/*
 * tracking_node.h
 *
 *  Created on: 05/12/2017
 *      Author: Jonathan Ginés
 */

#ifndef TRACKINGNODE_H_
#define TRACKINGNODE_H_

#include <ros/ros.h>
#include <string>
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <time.h>
#include <sstream>
namespace tracking_node {


class TrackingNode {
public:

	TrackingNode();

	virtual void step();
	virtual void imgCallback(const sensor_msgs::Image::ConstPtr& img_in);

private:
	ros::NodeHandle nh_;
	ros::NodeHandle private_nh_;
	ros::Subscriber image_sub;
	image_transport::ImageTransport it_;
	image_transport::Publisher image_pub;
	int hupper, hlower,x,y,c,supper,slower,vupper,vlower;

};

}

#endif /* TRACKINGNODE_H_ */
