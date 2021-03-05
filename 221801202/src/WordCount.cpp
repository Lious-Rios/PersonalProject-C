#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>  
const int rowsPerPar=4;//每段的最大行数、
const int wordsPerRow=15;//每行单词数、
const int wordsmax=300;//最大单词数
const int wordslength=7;//单词长度

using namespace std;
int num=0,i,lines=0,validnum=0;
 
class Paper{//对文件的文章类 
public:
	void fread(char * filename);
	void fwrite(char * filename);
private:
	map<string,int> words;
};

class Words{ //单词类
	public:
		string word; //单词
		int cnt; //数量
};

int cmpare(const pair<string, int>& x, const pair<string, int>& y)  {  //value比较 
    return x.second > y.second;   
}  
   
void sort(map<string, int>& tMap,vector<pair<string, int> >& wordVector)  {  //词频排序 
    for (map<string, int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)   
        wordVector.push_back(make_pair(curr->first, curr->second));    
   
    sort(wordVector.begin(), wordVector.end(), cmpare);  
}  

bool isSeparator(char c){//判断分隔符：所有非数字且非字母 
	return !(isupper(c)||islower(c)||isdigit(c));
}

int getCharNum(Words *words) {//从单词中统计字符 
	ifstream fin,in;
	ofstream fout;
	fin.open("input.txt",ios::in | ios::out | ios::binary);//打开文件
	fout.open("output.txt",ios::in | ios::out | ios::binary);//写入文件 
	if(!fin) {
		cout<<"文件打开错误！"<<endl;
		return -1;
	}
	int num=0,i,charnum=0,lines=0;
	char c;
	in.open("input.txt",ios::in);
	while(!in.eof())
	{	 
	if(c!='\n') charnum++;
	  else
	   charnum+=0;
		in>>c;
	}
	in.close();
	string word;
		while(fin) {
			fin>>word; //从文件读单词
			if(!fin) {
				break;//文件结尾 
			}
			bool flag = false;
			for(i=0;i<num;i++) {
				if(word==words[i].word) { //每次从数组中如果找到该单词
					flag=true;//单词标记为"相同" 
					words[i].cnt++; //该单词的数量加一 
					break;
				}
			}
			
			if(!flag) { //单词标记为"不同" 
				words[i].cnt=1; //新的单词计数为1
				words[i].word=word; //保存该单词
				num++; //单词种类加一 
			}
		}
	fout<<"characters:"<<charnum-1<<endl; 
	fin.close(); //关闭文件
	fout.close();//关闭文件 
	return charnum; //返回字符数
}
 
bool isValidWord(string str){//判断有效单词 
	if (str.length()<4)
		return false;
	char c[10000];
	strcpy(c,str.c_str());//转为字符数组 
	for (int i=0;i<4;i++){
		if((!(isupper(c[i])||islower(c[i])))){
					
			return false;
		}	
	}
}

int CountLines(char *filename){//获取行数 
	ifstream ReadFile;
	int n=0;
	char line[wordsmax/wordsPerRow];
	string temp;
	ReadFile.open(filename,ios::in);//用只读的方式读取文件
	if(ReadFile.fail())//文件打开失败:返回0
	{
	   return 0;
	}
	else//文件存在
	{
	while(getline(ReadFile,temp)!=NULL)
	{
	 
	   n++;
	}
	    return n;
	}
	ReadFile.close();
}

void createPaperAuto(){//随机文章生成器 

	int rcnt=0,wcnt=0,wcntPerRow=0,lines=1,charNum=0;//行数计数器，单词数计数器 ,行数 ,字符数 
	ofstream fout1,fout2;//写文件 
	fout1.open("input_random.txt");
	fout2.open("output_random.txt");
	int n=rand()%(3*wordsmax/4)+wordsmax/4;//单词限制 (k/4~k),使文章内容尽量饱满 
	cout<<"得到"<<n<<"个初始单词的文章:"<<endl;
	cout<<"    ";//首行缩进四个字符	
	fout1<<"        ";		
	while(n--)                              //生成单词 
	{
		int k=rand()%wordslength+4;         //每个单词的长度 
		for(int i=1;i<=k;i++)
		{
			int x;
			x=rand()%('~'-'!'+1)+'!';//生成从'!'到'~'的字符，对应ASCII码从33~127，其它键盘上没有 
			charNum++;
			printf("%c",x);
			fout1<<(char)x;				
		}
		printf("   ");//一个单词生成后的间隔
		fout1<<"   ";
		if (wcntPerRow==wordsPerRow){ 
			cout<<endl; 
			fout1<<endl;
			rcnt++;//行计数器+1
			lines++;//行数+1 
			if (rcnt>=rand()%rowsPerPar+1){//每段最大rowsPerPar行，最少1行
				cout<<"    ";//新的段落首行缩进4个字符 
				fout1<<"        ";
				rcnt=0;//下一段重新计数 
			} 
			wcntPerRow=0;//下一行重新计数 
		}						 
		wcnt++;//单词计数器
		wcntPerRow++;//每行单词计数器 
				
	}		
	cout<<endl<<endl<<"文章写入完成！"<<endl;
	fout2<<"characters:"<<charNum<<endl; 
	fout2<<"words:"<<wcnt<<endl;	//初步统计，之后会改为统计有效单词 
	fout2<<"lines:"<<lines<<endl;
	fout1.close();
	fout2.close();
} 

void countCharNum(){//输出字符个数 
	Words words[wordsmax] = {"",0}; //单词对象变量定义与初始化
	ofstream fout;
	fout.open("output.txt");
	int n=getCharNum(words); //获取字符数 
	fout<<"characters:"<<n<<endl;
	fout.close();
} 

void Paper::fread(char * filename){//读文件 
	ifstream ifs(filename);//打开文件流
	if(ifs.fail())
	{
		cout <<"ifstream open file error"<<endl;
		return;
	}
	string word;
	while( ifs >> word)
	{
		if(isValidWord(word))//如果为有效单词 
		words[word]++;
	}
 	ifs.close();
}
 
void Paper::fwrite(char * filename){//写文件 
	int wcnt=0,wtype=0;//单词数量和单词种类 
	ifstream fin;
	ofstream fout;
	int s=CountLines("input.txt");
	fin.open("input.txt",ios::app|ios::out);//打开文件 
	fout.open("output.txt",ios::app|ios::out);
	if(fin.fail())
	{
		cout <<"ifstream open file error"<<endl;
		
	}
    map<string, int> tMap;  
    string word; 
    while (fin >> word)  
    {  	
		transform(word.begin(),word.end(),word.begin(),::tolower);
	    if(isValidWord(word)){
	        pair<map<string,int>::iterator,bool> ret = tMap.insert(make_pair(word, 1));  
	        if (!ret.second)  
	            ++ret.first->second; 
				wcnt++;
		} 
    }   
    vector<pair<string,int> > tVector; //最后两个>>要隔开 
    sort(tMap,tVector);
    fout<<"lines:"<<s<<endl;
    fout<<"words:"<<wcnt<<endl;
    if (tVector.size()>10){
		fout<<"频率最高的10个单词如下:"<<endl;
    	for(int i=0;i<10;i++)
    		fout<<tVector[i].first<<": "<<tVector[i].second<<endl;
	}
    else{
    	fout<<"频率最高的"<<tVector.size()<<"个单词如下:"<<endl;
		for(int i=0;i<tVector.size();i++)  
	    	fout<<tVector[i].first<<": "<<tVector[i].second<<endl;
	}
	fin.close();
	fout.close();
}

int main(int argc,char **argv){  
	if(argc!=3){
		cout <<"输入input.txt/output.txt"<<endl;
	}
	countCharNum();
	Paper p;
	p.fread(argv[1]);//input.txt
	p.fwrite(argv[2]);//output.txt
	cout<<"请在output.txt查看结果！";
	return 0;
}














