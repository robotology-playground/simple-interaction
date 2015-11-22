--
-- Copyright (C) 2012 IITRBCS
-- Authors: Ali Paikan
-- CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
--

-- loading lua-yarp binding library
require("yarp")

--
-- create is called when the port monitor is created
-- @return Boolean
--
PortMonitor.create = function(options)
    -- set the constraint here
    PortMonitor.setConstraint("true")
    return true;
end

--
-- accept is called when the port receives new data
-- @param thing The Things abstract data type
-- @return Boolean
-- if false is returned, the data will be ignored
-- and update() will never be called
PortMonitor.accept = function(thing)
    PortMonitor.setEvent("e_face", 3.0)     -- the event will be expired after 3s
    return true
end

