/*author: HRITHIK KANOJE, RISHABH SINGH
Class: CS5330 Pattern Recog & Computer Vision
Prof: Bruce Maxwell
Final project
*/
#include<stdio.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]){
  if(argc!=2){
    printf("usage: DisplayImage.out <Image_path>\n");
    return(-1);
  }

  cv::Mat img,gray,blured,edges,roi;
  img = cv::imread(argv[1],1);
  if (!img.data)
  {
    printf("No Image Data! \n");
    return(-1);
  }
  cv::namedWindow("input",1);
  cv::imshow("input",img);
  cv::Size sz = img.size();
  int img_w = sz.width;
  int img_h = sz.height;
  
  roi = img(Rect(0,img_h/2,img_w,img_h/2)); //taking roi
  // cv::namedWindow("region of interest",1);
  // cv::imshow("region of interest",roi);

      cv::Mat output;
    cv::Point2f srcPoints[] ={
    cv::Point(1,324), //1 154
    cv::Point(959,324), //427 154
    cv::Point(0,539), //0 322
    cv::Point(960,538), //428 320
    };
    
    cv::Point2f dstPoints[] ={
    cv::Point(0,0),  //0 0
    cv::Point(957,0), //427 0
    cv::Point(0,540), //1 322
    cv::Point(960,538), //428 320
    };

    cv::Mat Matrix = cv::getPerspectiveTransform(srcPoints,dstPoints);

    cv::warpPerspective(img,output,Matrix,roi.size()); //convert to bird's eye view

  //   cv::namedWindow("bird's eye view",1);
  // cv::imshow("bird's eye view",output);
  
  cv::cvtColor(output,gray,COLOR_BGR2GRAY); //convert to grayscale
  // cv::namedWindow("grayscale",1);
  // cv::imshow("grayscale",gray);
  cv::GaussianBlur(gray,blured,Size(5,5),0); //perform gaussain blur
  // cv::namedWindow("GaussianBlur",1);
  // cv::imshow("GaussianBlur",blured);
  cv::Canny(blured,edges,50,100,3,false); //apply canny edge detector
  // cv::namedWindow("edges",1);
  // cv::imshow("edges",edges);


  vector<Vec4i> lines; //create a vector to store line of the image


  HoughLinesP(edges,lines,5,CV_PI/180,120,10,10); //perform Hough tranform

  for(size_t i=0; i<lines.size(); i++){
    Vec4i l =lines[i];
    line(output, Point(l[0],l[1]), Point(l[2], l[3]), Scalar(0,255,0), 3, LINE_AA);
  }

  cv::namedWindow("Detected Lanes",1);
  cv::imshow("Detected Lanes",output);






  // cv::namedWindow("HT",1);
  // cv::imshow("HT",roi);

  cv::waitKey(0);

  // std::cout<<"W:" <<img_w;
  // std::cout<<"H:" <<img_h;
    return (0);
}