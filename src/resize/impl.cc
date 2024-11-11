#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    cv::Mat output = cv::Mat::zeros(new_rows, new_cols, input.type());
    // IMPLEMENT YOUR CODE HERE
    for (int i=0;i<new_rows;++i) 
    {
        for (int j=0;j<new_cols;++j) 
        {
            float i1=i/scale;
            float j1=j/scale;

            int i2=static_cast<int>(i1);
            int j2=static_cast<int>(j1);

            float x=j1-j2;
            float y=i1-i2;

            int x1=j2;
            int y1=i2;
            int x2=(x>0)?x1+1:x1;
            int y2=(y>0)?y1+1:y1;
            x2=(x2>=input.cols)?input.cols-1:x2;
            y2=(y2>=input.rows)?input.rows-1:y2;



            for (int k = 0; k < input.channels(); ++k) 
            {
                float q11 = input.at<cv::Vec3b>(y1, x1)[k];
                float q21 = input.at<cv::Vec3b>(y1, x2)[k];
                float q12 = input.at<cv::Vec3b>(y2, x1)[k];
                float q22 = input.at<cv::Vec3b>(y2, x2)[k];

                float r1 = q11 + (q21 - q11) * x;
                float r2 = q12 + (q22 - q12) * x;

                float val = r1 + (r2 - r1) * y;

                output.at<cv::Vec3b>(i, j)[k] = static_cast<uchar>(val);
            }
           
        }
    }
    return output;
}