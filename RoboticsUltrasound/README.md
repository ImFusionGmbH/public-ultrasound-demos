# Robotics Ultrasound Demo

This demo attempts to show the capabilities of the ImFusionSuite to perform an Robotics Ultrasound simulation in which, from an already segmented CT scan and a simulated Robot with an ultrasound probe as a tool at the TCP, a simulated US scan can be run.

In order to run the demo:
1. Run `ImFusionSuite SimFrankaHolder.iws`
2. Open the `ProcessedCT.imf` in the Suite, either drag-and-drop or using the `Open` utility in the upper bar of the Suite
3. Select the new `ProcessedCT` and the `Robot US Tracking Stream` on the `Data` section, right-click somewhere on the `Data` section, Ultrasound->Advanced->Virtual Imaging Algorithm. Click `Start stream`.
3. Select `Robot US TrackingStream` and `Image Stream` on the `Data` section, right-click somewhere on the `Data` section, Ultrasound->Record Ultrasound Sweeps
    - In the `Advanced settings` section, reduce the `Sweep buffer` from 50 to 1 to improve performance
4. Move around with the TCP of the robot to simulate what a ultrasound scan would look like

If you adjust the short-long radius of the Virtual Imaging Algorithm, don't forget to adjust the Calibration data of the Tracking stream: select the `Robot US Tracking Stream` in the `Data` section, right-click on the `Data` section, Streaming->Tracking Stream Properties
Some considerations:
- The x-y axis are the ones contained in the plane of the slice that you can see
- The y-direction is the one that goes on the same direction as the z-axis of the TCP of the Robot
- A tuning of this is needed because the computation of the slice is performed based on this parameter, which with a (x,y,z) = (0,0,0) in the translational part of the calibration, it will interpret that the center of the slice is at the same point as the origin of the tracking pose (which, in this case, is the TCP of the robot)

## Additional considerations

All the other source files show how a new Algorithm can be integrated into the ImFusion Suite. In particular, the CTToMediumAlgorithm files implement an algorithm that gets the output of a Segmentation Map from a CT (using one of our Machine Learning models), and rename the labels to the type of medium/material that the Ultrasound simulation will use. All the other header/implementation files show how then that algorithm can be integrated into the Suite by creating a new Plugin (RoboticsUltrasoundDemoPlugin).
