// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
/* 
 * Copyright (C) 2012 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Ali Paikan
 * email:  ali.paikan@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include "wonder.h"
#include <yarp/os/Vocab.h>
 
using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::math;

#define GAZE_REST_X               -7.0
#define GAZE_REST_Y               0.0
#define GAZE_REST_Z               0.0

#define GAZE_X_MIN                -3.0
#define GAZE_X_MAX                -2.0
#define GAZE_Y_MIN                -1.0
#define GAZE_Y_MAX                1.0
#define GAZE_Z_MIN                0.0
#define GAZE_Z_MAX                0.7	

 
const double RIGHT_RELAX_POS[7] = { -0.29, 0.21, 0.02, -0.14, -0.79, 0.59, 3.06}; 
const double LEFT_RELAX_POS[7] = { -0.29, -0.21, 0.02, -0.03, 0.60, -0.79, 2.85}; 

void Wonder::loop()
{

    Bottle &target=targetPort.prepare();
    target.clear();
    target.addDouble(Rand::scalar(GAZE_X_MIN,GAZE_X_MAX));
    target.addDouble(Rand::scalar(GAZE_Y_MIN,GAZE_Y_MAX));
    target.addDouble(Rand::scalar(GAZE_Z_MIN,GAZE_Z_MAX));
    targetPort.write();

    Bottle &cmd=faceExpPort.prepare();
    cmd.addVocab(Vocab::encode("set"));
	cmd.addVocab(Vocab::encode("all"));
	cmd.addVocab(Vocab::encode(faceExpression.c_str()));
	faceExpPort.write();
}


bool Wonder::open(yarp::os::ResourceFinder &rf) {
    faceExpression = rf.check("expression", Value("shy")).asString().c_str();
    Rand::init();

    bool ret=true;   
    ret = targetPort.open("/wonderAround/gazeXd:o");    
    ret &= faceExpPort.open("/wonderAround/face:o");
    return ret;
}

bool Wonder::close() {    
    gazeRest();
    targetPort.close();   
    faceExpPort.close();
    return true;
}

bool Wonder::interrupt() {
    return true;
}

void Wonder::gazeRest()
{
    Bottle &target=targetPort.prepare();
    target.clear();
    target.addDouble(GAZE_REST_X);
    target.addDouble(GAZE_REST_Y);
    target.addDouble(GAZE_REST_Z);
    targetPort.setStrict();
    targetPort.write();    
}   
