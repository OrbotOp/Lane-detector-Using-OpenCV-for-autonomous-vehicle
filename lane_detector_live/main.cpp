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

int main(int argc, char *argv[]) {
        cv::VideoCapture *capdev;

        // open the video device
        capdev = new cv::VideoCapture(2);
        if( !capdev->isOpened() ) {
                printf("Unable to open video device\n");
                return(-1);
        }

        // get some properties of the image
        cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                       (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("Expected size: %d %d\n", refS.width, refS.height);

        cv::Mat frame,gray,blured,edges,roi;

        for(;;) {
                *capdev >> frame; // get a new frame from the camera, treat as a stream
                if( frame.empty() ) {
                  printf("frame is empty\n");
                  break;
                }    
                cv::imshow("Input", frame);

                char key = cv::waitKey(10); // see if there is a waiting keystroke
                if( key == 'q') 
                    break;

                if(key == 'e'){
                  for(;;){
                    *capdev>>frame;
                    cv::cvtColor(frame,gray,COLOR_BGR2GRAY); //convert to grayscale
                    cv::GaussianBlur(gray,blured,Size(5,5),0); //apply gaussian blur
                    cv::Canny(blured,edges,50,100,3,false);    //apply canny edge detector        
                    
                    vector<Vec4i> lines; //create a vector to store line of the image
                    HoughLinesP(edges,lines,1,CV_PI/180,120,10,10); //perform Hough tranform 160,10,10
                    for(size_t i=0; i<lines.size(); i++){
                        Vec4i l =lines[i];
                        line(frame, Point(l[0],l[1]), Point(l[2], l[3]), Scalar(0,255,0), 3, LINE_AA);
                    }
                    // cv::Size sz = frame.size();
                    // int frame_w = sz.width;
                    // int frame_h = sz.height;
  
                    // roi = frame(Rect(0,frame_h/2,frame_w,frame_h/2));
                        cv::Mat output;
                        cv::Point2f srcPoints[] ={
                        cv::Point(1,250), //1 154
                        cv::Point(637,250), //427 154
                        cv::Point(0,477), //0 322
                        cv::Point(638,478), // 428 320
                        };
    
                        cv::Point2f dstPoints[] ={
                        cv::Point(0,0),  //0,0
                        cv::Point(637,0), //427,0
                        cv::Point(0,477), //0,322
                        cv::Point(638,478), //428,320
                        };

                        cv::Mat Matrix = cv::getPerspectiveTransform(srcPoints,dstPoints); //bird's eye view

                        cv::warpPerspective(frame,output,Matrix,frame.size());
                    cv::namedWindow("HT",1);
                    cv::imshow("HT",output);
                    // cv::waitKey(0);
                    char dk1=waitKey(10);
                    if(dk1 =='e'){
                     destroyAllWindows();
                     break;
                } 
                }

                
                } 

             
        }

        delete capdev;
        return(0);
}