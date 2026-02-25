#include "ImFusion/GL/SharedImageSet.h"

#include <ImFusion/Base/Algorithm.h>
#include <ImFusion/Base/Data.h>
#include <ImFusion/Base/DataComponent.h>
#include <ImFusion/Base/LabelDataComponent.h>
#include <ImFusion/Base/Mask.h>
#include <ImFusion/Base/TypedImage.h>
#include <ImFusion/Core/Log.h>
#include <ImFusion/Core/Signal.h>
#include <ImFusion/ML/BoundingBoxSet.h>

#include <CTToMediumAlgorithm.h>
#include <memory>

namespace ImFusion::US
{
	CTToMediumAlgorithm::CTToMediumAlgorithm(SharedImageSet* data)
		: m_data(data){};

	CTToMediumAlgorithm::~CTToMediumAlgorithm() = default;

	bool CTToMediumAlgorithm::createCompatible(const DataList& data, Algorithm** a)
	{
		auto d = data.getAll<SharedImageSet>();
		if (d.size() != 1)
		{
			return false;
		}
		if (d[0]->components().get<LabelDataComponent>() == nullptr)
		{
			return false;
		}
		if (a)
			*a = new CTToMediumAlgorithm(d[0]);
		return true;
	};

	void CTToMediumAlgorithm::compute()
	{
		LabelDataComponent* labelDataComponent = m_data->components().get<LabelDataComponent>();
		auto dataCopy = labelDataComponent->labelConfigs();
		for (auto& p : dataCopy)
		{
			if (mapCTOutputUSMedium.find(p.second.name) != mapCTOutputUSMedium.end())
				p.second.name = mapCTOutputUSMedium.at(p.second.name);
			else
				LOG_INFO("No current conversion for value: " << p.second.name);
		}

		// Create new label to mimic water around the tissue
		const auto& desc = m_data->img()->descriptor();
		auto labelImg = std::make_unique<TypedImage<unsigned char>>(desc.dimensions(), 1);
		int newLabelValue = 1;
		while (labelDataComponent->hasLabel(newLabelValue) && newLabelValue < 255)
			newLabelValue++;

		LabelDataComponent::LabelConfig newLabel;
		newLabel.name = "Water";
		newLabel.color = vec4(1.0, 0.0, 0.0, 0.5);    // RGBA, e.g., vec4(1, 0, 0, 0.5) for semi-transparent red
		newLabel.isVisible2d = true;
		newLabel.isVisible3d = false;
		dataCopy[newLabelValue] = newLabel;

		int borderSize = 100;

		for (int frame = 0; frame < m_data->size(); ++frame)
		{
			SharedImage* oldImg = m_data->get(frame);
			auto mask = oldImg->mask();

			const int oldW = oldImg->width();
			const int oldH = oldImg->height();
			const int oldS = oldImg->slices();
			const int newW = oldW + 2 * borderSize;
			const int newH = oldH + 2 * borderSize;
			const int newS = oldS + 2 * borderSize;

			auto newTypedImg = std::make_shared<TypedImage<unsigned char>>(vec3i(newW, newH, newS), 1);
			newTypedImg->fill(newLabelValue);

			auto* oldTypedImg = oldImg->mem()->typed<unsigned char>();
			if (!oldTypedImg)
				continue;

			unsigned char* oldPtr = oldTypedImg->pointer();
			unsigned char* newPtr = newTypedImg->pointer();


			for (int z = 0; z < newS; ++z)
			{
				for (int y = 0; y < newH; ++y)
				{
					for (int x = 0; x < newW; ++x)
					{
						size_t newIdx = x + y * newW + z * newW * newH;

						bool isBorder = x < borderSize || y < borderSize || z < borderSize || x >= (borderSize + oldW) || y >= (borderSize + oldH) ||
										z >= (borderSize + oldS);
						if (!isBorder)
						{
							size_t oldIdx = x - borderSize + (y - borderSize) * oldW + (z - borderSize) * oldW * oldH;
							bool isMaskedOut = false;
							if (mask)
								isMaskedOut = (mask->maskValue(vec3i(x - borderSize, y - borderSize, z - borderSize)) == 0);
							else
								isMaskedOut = (oldPtr[oldIdx] == 0);    // Or use whatever condition defines "not good"

							if (!isMaskedOut)
								newPtr[newIdx] = static_cast<unsigned char>(oldPtr[oldIdx]);
						}
					}
				}
			}
			LOG_INFO("Finished assigning values, assigning image now...");
			oldImg->assign(newTypedImg);
			oldImg->setDirtyMem();
		}

		LOG_INFO("Finished computation, finalizing some details...");
		labelDataComponent->setLabelConfigs(dataCopy);

		labelDataComponent->signalChanged.emitSignal(labelDataComponent);
	}

	OwningDataList CTToMediumAlgorithm::takeOutput()
	{
		auto boundingBoxSet = std::make_unique<ML::BoundingBoxSet>();

		return OwningDataList{std::move(boundingBoxSet)};
	}

	CTToMediumController::CTToMediumController(CTToMediumAlgorithm* alg)
		: DefaultAlgorithmController(alg, "")
		, m_alg(alg){};
	void CTToMediumController::onCompute() { m_alg->compute(); }

}    // namespace ImFusion::US
