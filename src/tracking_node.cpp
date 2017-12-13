/*
 *
 *
 * Autor: Jonathan Ginés Clavero (jonathangines@hotmail.com)
 *
 *
 */

#include "proc_imagen_mj/tracking_node.h"

namespace tracking_node {

	TrackingNode::TrackingNode():
		it_(nh_),
  	private_nh_("~"){
			image_sub = nh_.subscribe("/camera/rgb/image_raw", 5, &TrackingNode::imgCallback,this);
			image_pub = it_.advertise("/image_converter/output", 1);
			cvNamedWindow("Imagen filtrada");
			hlower = 112;
			hupper = 149;
			slower = 242;
			supper = 255;
			vlower = 90;
			vupper = 255;
	}


	void
	TrackingNode::imgCallback(const sensor_msgs::Image::ConstPtr& img_in){
		cv_bridge::CvImagePtr cv_ptr, cv_imageout;
    try
    {
         cv_ptr = cv_bridge::toCvCopy(img_in, sensor_msgs::image_encodings::BGR8);
         cv_imageout = cv_bridge::toCvCopy(img_in, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
         ROS_ERROR("cv_bridge exception: %s", e.what());
         return;
    }

    cv::Mat hsv;
    cv::cvtColor(cv_ptr->image, hsv, CV_RGB2HSV);

    int height = hsv.rows;
    int width = hsv.cols;
    int step = hsv.step;
    int channels = 3;

    x = 0;
    y = 0;
    c = 0;

		cv::HOGDescriptor hog;
	 	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
	 	cv::namedWindow("people detector", 1);
		std::vector<cv::Rect> found, found_filtered;
		hog.detectMultiScale(cv_ptr->image, found, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 2);


    for(int i = 0; i <height; i++ )
    	for(int j = 0; j <width; j++ ) {
				int posdata = i*step+j*channels; //Only H channel
				if(!((hsv.data[posdata] >= hlower) && (hsv.data[posdata] <= hupper) &&
					(hsv.data[posdata+1]>=slower)&& (hsv.data[posdata+1] <= supper)&&
					(hsv.data[posdata+2] >= vlower)&&(hsv.data[posdata+2] <= vupper))){
						cv_imageout->image.data[posdata] = 0;
						cv_imageout->image.data[posdata+1] = 0;
						cv_imageout->image.data[posdata+2] = 0;
				}else{
					x = x + j;
					y = y + i;
					c++;
				}
			}
			int coorX = x/c;
			int coorY = y/c;
			ROS_INFO("Coordenada centro pelota %d %d",coorX,coorY);
			cv::Point p;
			p.x = coorX;
			p.y = coorY;
			cv::circle(cv_imageout->image,p, 20, (0,0,255));
			cv::imshow("Imagen filtrada", cv_imageout->image);
			cv::waitKey(3);
    	image_pub.publish(cv_imageout->toImageMsg());
	}

	void
	TrackingNode::step(){

	}
}

using namespace tracking_node;

int
main(int argc, char** argv)
{
	ros::init(argc, argv, "tracking_node");		//Inicializa el nodo
	TrackingNode tr_node;
	ros::Rate loop_rate(20);

	/*while (ros::ok()){
  	tr_node.step();
		ros::spinOnce();
		loop_rate.sleep();
	}*/
	ros::spin();
	return 0;
}
