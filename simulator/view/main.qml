/***************************************************************************
 * Copyright (C) 2020 by EWT                                               *
 *                                                                         *
 * All Rights Reserved.                                                    *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * Author: Erik Miers                                                      *
 * Email: erik.miers@gmail.com                                             *
 ***************************************************************************/

import QtQuick 2.15
import QtQuick.Scene3D 2.15
import QtQuick 2.0 as QQ2

import Qt3D.Core 2.15
import Qt3D.Render 2.15
import Qt3D.Input 2.15
import Qt3D.Extras 2.15
import Qt3D.Logic 2.15

import ewt.sim 1.0 as SIM


Item {


	Rectangle {
		id              : scene
		anchors.fill    : parent
		anchors.margins : 50
		color           : "darkBlue"


		Scene3D {
			id              : scene3d
			anchors.fill    : parent
			anchors.margins : 10
			focus           : true
			aspects         : ["input", "logic"]

			cameraAspectRatioMode : Scene3D.AutomaticAspectRatio


			Entity {
				id : sceneRoot


				Camera {
					id             : camera
					projectionType : CameraLens.PerspectiveProjection
					fieldOfView    : 45
					nearPlane      : 0.1
					farPlane       : 1000.0
					position       : Qt.vector3d( 0.0, 0.0, 40.0 )
					upVector       : Qt.vector3d( 0.0, 1.0, 0.0 )
					viewCenter     : Qt.vector3d( 0.0, 0.0, 0.0 )
				} // Camera


				FirstPersonCameraController { camera: camera }


				components: [

					RenderSettings {
						id               : renderSettings
						activeFrameGraph : ForwardRenderer {
							camera           : camera
							clearColor       : "transparent"
							showDebugOverlay : false
						}
					},

					InputSettings { }
				]


				SIM.GranuleItemModel {
					id   : granuleItemModel
					size : 20
				}


				FrameAction {
					onTriggered: granuleItemModel.update(dt)
				}


				NodeInstantiator {
					model    : granuleItemModel
					delegate : Entity {
//						property double

						components : [
							SphereMesh{ radius: 0.3},
							PhongMaterial {},
//							Transform { translation: Qt.vector3d(x, y, 0) }
							Transform { translation: modelPosition }
						]

					} // delegate Entity

				} // NodeInstantiator Granules

			} // Entity Scene Root

		} // Scene3D

	} // Rectangle Scene

} // Item MainWindow
