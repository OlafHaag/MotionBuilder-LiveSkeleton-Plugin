# MotionBuilder-LiveSkeleton-Plugin
MotionBuilder OpenReality Input Device Plugin for skeleton joint data.

This plugin for Autodesk's MotionBuilder is an input device that connects to a [thrift](https://thrift.apache.org/) server to retrieve data on skeleton joints for creating the skeleton and animating it in real-time.

At the time of creation of this plugin I was learning about the MotionBuilder API and needed a quick solution for streaming animation data for skeletons of arbitrary topologies. I had a hard time compiling the dependencies and unfortunately wasn't able to compile a debug version of the plugin (catch statements are very broad). The plugin is therefore not the most stable one and you'll probably experience crashes of Motionbuilder when using it “incorrectly”. So I advice against using the plugin for production.

I turned to a RPC (Remote procedure call) framework, because I'm neither an expert in network-programming, nor in C++ programming. I chose thrift, because of its cross-language capabilities, because it can be compiled with VS2012 and because of its license.

## Requirements
- up to MotionBuilder2018: Visual Studio 2012 or its v110 toolset
- since MotionBuilder2019: Visual Studio 2015 Update 3
- thrift libraries and its IDL compiler
- boost libraries
- some environment variables for use with the provided VS project:
  - MOBU_DIR: Path to MotionBuilder installation folder
  - BOOST_ROOT: Path to your boost folder
  - THRIFT_DIR: Path to your thrift folder

    You may or may not need:
  - OPENSSL_ROOT_DIR: path to [openssl](https://www.openssl.org/) folder
  - LIBEVENT_DIR: Path to your thrift libevent folder. I guess you only need it if you want to write a server in C++.

## How to use
Start your server.
Drag the plugin __»LiveSkeleton«__ from your Asset Browser>Templates>Devices into the scene. You can change the IP Adress for the server and the port, as well as the sample rate in the _Setup_ tab. Hit the _Online_ label. If the plugin successfully connected to your server the red square to the left turns green and you see data streaming in on the _Joints_ tab. If your server was not ready, it sometimes can take up to a minute until MotionBuilder is responding again.
From the _Model binding_ dropdown choose _Create ..._ and then hit the _Live_ label.

There are 2 other features in the _properties_ of the device.
- UseReferenceTransformation: Check this if you want to move the skeleton around by its reference joint.
- Global Data incoming: Check this if your data stream contains the global/world positions of the joints.

## Sample Python Server
To test the plugin I wrote a dummy server in python which streams a bvh file.
It works best when you stream the data in world coordinates to avoid rotation errors. Just append the _-w_ flag to the *python test_server.py »path-to-bvh-file«* command and check _Global Data Incoming_ in the device's properties.
