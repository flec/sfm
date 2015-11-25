//
// Created by joschi on 25.11.15.
//

#include "pointviewer.h"


// Draws a spiral
void PointViewer::draw() {
  glPointSize(5.0);

  float pos[4] = {0.0, 0.5, 1.0, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  drawLight(GL_LIGHT0);

  glBegin(GL_POINTS);
  vector<shared_ptr<ObjectPoint>> *object_points = sfmapp->get_object_points();

  glColor3f(0.862745f, 0.0784314f, 0.235294f);
  for (auto object_point : *object_points) {
    glVertex3d(object_point->coordinates()->x, object_point->coordinates()->y,
               object_point->coordinates()->z);
  }
  glEnd();
}

// Constructor must call the base class constructor.
PointViewer::PointViewer(QWidget *parent) : QGLViewer(parent), sfmapp(SFMApp::getInstance()) {
  // Opens help window
  help();
  glEnable(GL_LIGHT0);
  qglviewer::Vec camera_position(0, 0, 40);
  camera()->setPosition(camera_position);
  camera()->lookAt(sceneCenter());
  setSceneBoundingBox(qglviewer::Vec(-5,-5,-5), qglviewer::Vec(5,5,5));

  showEntireScene();
}

QString PointViewer::helpString() const {
  QString text("<h2>S i m p l e V i e w e r</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
  text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
  text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}
