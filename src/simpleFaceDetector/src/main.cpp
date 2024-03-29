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
#include <stdio.h>
#include <yarp/os/Network.h>


#include "Detector.h"
#include <yarp/os/RFModule.h>

using namespace yarp::os;

class DetectorModule: public RFModule
{
   Detector* detector;

public:

    DetectorModule()
    {
        detector = new Detector();
    }

    ~DetectorModule()
    {
        delete detector;        
    }


    bool configure(ResourceFinder &rf)
    {
        ConstString cascade;
        if(!rf.check("cascade") /*|| !rf.check("nested-cascade")*/)
            cascade = "haarcascade_frontalface_alt.xml";
        else
            cascade = rf.find("cascade").asString();
        detector->strCascade = rf.findFile(cascade);
        printf("cascade: %s\n", detector->strCascade.c_str());
        //detector->strNestedCascade= rf.find("nested-cascade").asString();
        return detector->open(rf);
    }

    double getPeriod()
    {
        return 0.00;
    }
    
    bool updateModule()
    { 
        detector->loop();
        return true; 
    }

    bool interruptModule()
    {
        fprintf(stderr, "Interrupting\n");
        detector->interrupt();
        return true;
    }

    bool close()
    {
        fprintf(stderr, "Calling close\n");
        detector->close();
        return true;
    }

};

int main(int argc, char *argv[]) 
{
    Network yarp;
    //YARP_REGISTER_DEVICES(icubmod)

    DetectorModule module;
    ResourceFinder rf;
    rf.setVerbose();
	rf.setDefaultConfigFile("face_detector.ini");
    rf.setDefaultContext("simpleFaceDetector");
    rf.configure(argc, argv);
   
    if (!module.configure(rf)) {
        fprintf(stderr, "Error configuring module returning\n");
        return -1;
    }
    
    module.runModule();

    printf("Module shutting down\n");

    return 0;
}
