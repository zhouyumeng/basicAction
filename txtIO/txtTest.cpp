//该程序实现了目录.txt每行数据的获取，并对该行数据进行处理

#include <fstream>  
#include <string>  
#include <iostream> 
#include <time.h> 
using namespace std;

int main()  
{  
    clock_t start, end;
    start = clock();
    ifstream txtList("txtFileNameList.txt");             //读取.txt文件 
    string filename;
    if(txtList)                                          //对读取文件进行判断  
    {
        while (getline (txtList, filename))              //line中不包括每行的换行符，将每行的数据读取到line中  
        {
            cout << filename << endl;                    //输出每行的数据
            ifstream position(filename.c_str());         //首先将每行数据变成文件路径，再根据该路径生成文件流

            int positions[4];
            
            for(int i = 0; i < 4; i++)                   //将文件流中的数据输出到数组中
            {
                position >> positions[i];
                cout << positions[i] << endl;
            }

            string str;
            getline(position, str);

            int pos = str.find("&");                    //找到“&”字符，并通过该字符得到标签的起始位置

            string label = str.substr(pos+1, str.length());
            cout << label << endl;

            if(!txtList.good())
            break;
		
			position.close();
        }
    }
    else // 没有该文件  
    {
        cout <<"no such file" << endl;              
    }
	txtList.close();
    end = clock();
    printf("The time was: %f\n", (double)(end - start) / CLK_TCK);
    return 0;
}  
