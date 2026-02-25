#pragma once

#include <ImFusion/Base/Algorithm.h>
#include <ImFusion/Base/LabelDataComponent.h>
#include <ImFusion/Core/Signal.h>
#include <ImFusion/GUI/DefaultAlgorithmController.h>

#include <variant>

class QWindow;
class QWidget;

const std::unordered_map<std::string, std::string> mapCTOutputUSMedium = {
	{"Background", "Water"},
	{"rib_left_1", "Bone"},
	{"rib_left_2", "Bone"},
	{"rib_left_3", "Bone"},
	{"rib_left_4", "Bone"},
	{"rib_left_5", "Bone"},
	{"rib_left_6", "Bone"},
	{"rib_left_7", "Bone"},
	{"rib_left_8", "Bone"},
	{"rib_left_9", "Bone"},
	{"rib_left_10", "Bone"},
	{"rib_left_11", "Bone"},
	{"rib_left_12", "Bone"},
	{"rib_right_1", "Bone"},
	{"rib_right_2", "Bone"},
	{"rib_right_3", "Bone"},
	{"rib_right_4", "Bone"},
	{"rib_right_5", "Bone"},
	{"rib_right_6", "Bone"},
	{"rib_right_7", "Bone"},
	{"rib_right_8", "Bone"},
	{"rib_right_9", "Bone"},
	{"rib_right_10", "Bone"},
	{"rib_right_11", "Bone"},
	{"rib_right_12", "Bone"},
	{"skull", "Bone"},
	{"sternum", "Bone"},
	{"costal_cartilages", "Soft Tissue"},
	{"spleen", "Soft Tissue"},
	{"kidney_right", "Soft Tissue"},
	{"kidney_left", "Soft Tissue"},
	{"gallbladder", "Soft Tissue"},
	{"liver", "Liver"},
	{"stomach", "Soft Tissue"},
	{"pancreas", "Soft Tissue"},
	{"adrenal_gland_right", "Soft Tissue"},
	{"adrenal_gland_left", "Soft Tissue"},
	{"lung_upper_lobe_left", "Soft Tissue"},
	{"lung_lower_lobe_left", "Soft Tissue"},
	{"lung_upper_lobe_right", "Soft Tissue"},
	{"lung_middle_lobe_right", "Soft Tissue"},
	{"lung_lower_lobe_right", "Soft Tissue"},
	{"esophagus", "Soft Tissue"},
	{"trachea", "Soft Tissue"},
	{"thyroid_gland", "Soft Tissue"},
	{"small_bowel", "Soft Tissue"},
	{"duodenum", "Soft Tissue"},
	{"colon", "Soft Tissue"},
	{"urinary_bladder", "Soft Tissue"},
	{"prostate", "Soft Tissue"},
	{"kidney_cyst_left", "Soft Tissue"},
	{"kidney_cyst_right", "Soft Tissue"},

	{"humerus_left", "Bone"},
	{"humerus_right", "Bone"},
	{"scapula_left", "Bone"},
	{"scapula_right", "Bone"},
	{"clavicula_left", "Bone"},
	{"clavicula_right", "Bone"},
	{"femur_left", "Bone"},
	{"femur_right", "Bone"},
	{"hip_left", "Bone"},
	{"hip_right", "Bone"},
	{"spinal_cord", "Bone"},
	{"gluteus_maximus_left", "Bone"},
	{"gluteus_maximus_right", "Bone"},
	{"gluteus_medius_left", "Bone"},
	{"gluteus_medius_right", "Bone"},
	{"gluteus_minimus_left", "Bone"},
	{"gluteus_minimus_right", "Bone"},
	{"autochthon_left", "Bone"},
	{"autochthon_right", "Bone"},
	{"iliopsoas_left", "Bone"},
	{"iliopsoas_right", "Bone"},
	{"brain", "Bone"},

	{"sacrum", "Bone"},
	{"vertebrae_S1", "Bone"},
	{"vertebrae_L5", "Bone"},
	{"vertebrae_L4", "Bone"},
	{"vertebrae_L3", "Bone"},
	{"vertebrae_L2", "Bone"},
	{"vertebrae_L1", "Bone"},
	{"vertebrae_T12", "Bone"},
	{"vertebrae_T11", "Bone"},
	{"vertebrae_T10", "Bone"},
	{"vertebrae_T9", "Bone"},
	{"vertebrae_T8", "Bone"},
	{"vertebrae_T7", "Bone"},
	{"vertebrae_T6", "Bone"},
	{"vertebrae_T5", "Bone"},
	{"vertebrae_T4", "Bone"},
	{"vertebrae_T3", "Bone"},
	{"vertebrae_T2", "Bone"},
	{"vertebrae_T1", "Bone"},
	{"vertebrae_C7", "Bone"},
	{"vertebrae_C6", "Bone"},
	{"vertebrae_C5", "Bone"},
	{"vertebrae_C4", "Bone"},
	{"vertebrae_C3", "Bone"},
	{"vertebrae_C2", "Bone"},
	{"vertebrae_C1", "Bone"},

	{"heart", "Muscle"},

	{"heart_myocardium", "Muscle"},
	{"heart_atrium_left", "Muscle"},
	{"heart_ventricle_left", "Muscle"},
	{"heart_atrium_right", "Muscle"},
	{"heart_ventricle_right", "Muscle"},
	{"pulmonary_artery", "Vessel"},
	{"face", "Muscle"},

	{"aorta", "Vessel"},
	{"pulmonary_vein", "Vessel"},
	{"brachiocephalic_trunk", "Vessel"},
	{"subclavian_artery_right", "Vessel"},
	{"subclavian_artery_left", "Vessel"},
	{"common_carotid_artery_right", "Vessel"},
	{"common_carotid_artery_left", "Vessel"},
	{"brachiocephalic_vein_left", "Vessel"},
	{"brachiocephalic_vein_right", "Vessel"},
	{"atrial_appendage_left", "Vessel"},
	{"superior_vena_cava", "Vessel"},
	{"inferior_vena_cava", "Vessel"},
	{"portal_vein_and_splenic_vein", "Vessel"},
	{"iliac_artery_left", "Vessel"},
	{"iliac_artery_right", "Vessel"},
	{"iliac_vena_left", "Vessel"},
	{"iliac_vena_right", "Vessel"},
};

namespace ImFusion
{
	namespace US
	{

		class CTToMediumAlgorithm : public Algorithm
		{
		public:
			explicit CTToMediumAlgorithm(SharedImageSet* data);
			~CTToMediumAlgorithm();

			static bool createCompatible(const DataList& data, Algorithm** a = 0);

			void compute() override;

			OwningDataList takeOutput() override;

			// void configure(const Properties* p) override;
			// void configuration(Properties* p) const override;

		private:
			SharedImageSet* m_data = nullptr;

			void setBoundingBox();
		};

		class CTToMediumController : public DefaultAlgorithmController
		{
		public:
			/// Constructor
			CTToMediumController(CTToMediumAlgorithm* alg);

			/// Adds additional label for amount of active elements
			// void init() override;

			void onCompute() override;

		private:
			CTToMediumAlgorithm* m_alg;
		};

	}    // namespace US
}    // namespace ImFusion
