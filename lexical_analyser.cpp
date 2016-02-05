#include<iostream>
#include<fstream>
using namespace std;



int is_char(char c)
{
	if((c>=65 && c<=90) || (c>=97 && c<=122))
             return 1;
    else
             return 0; 
}

int is_number(char c)
{
	if(c>=48 && c<=57)
             return 1;
    else
             return 0;
}

int is_operator(char a)
{
	int flag=0;
    char c[5]={'=',';',',','{','}'};
    for(int j=0;j<5;j++)
    {
    	if(a==c[j])
    	flag=1;
	}
	return flag;
}

int is_keyword(string s)
{
	int flag=0;
	string l[4]={"int","main()","float","if"};
	 for(int j=0;j<4;j++)
    {
    	if(s==l[j])
    	flag=1;
	}
	return flag;
}
int main()
{
	string strbuff;
	int strlen;
	int num_flag=0,char_flag=0,op_flag=0;
	
	ifstream ifs;
	ifs.open("input1.txt",ios::in);
	
	ofstream ofs;
	ofs.open("output1.txt",ios::out);
	while(!ifs.eof())
	{
			getline(ifs,strbuff);
			strlen=strbuff.length();
			string buffer="";
			strbuff=strbuff+" ";
			
			for(int i=0;i<strlen;i++)
			{
				char a=strbuff[i];
				cout<<"a"<<a<<endl;
				if(a==' '||a=='\t'||a=='\n')
				{
					if(num_flag==1)
					{
						ofs<<buffer<<"--------->"<<"num"<<endl;
						buffer="";
						num_flag=0;
					}
					
					if(char_flag==1)
					{
						if(is_keyword(buffer))
						{
							ofs<<buffer<<"--------->"<<"keyword"<<endl;
							char_flag=0;
							buffer="";
						}
						else 
						{
							ofs<<buffer<<"--------->"<<"identifier"<<endl;
						    char_flag=0;
						    buffer="";
						}	
					}
					
					if(op_flag==1)
					{
						ofs<<buffer<<"--------->"<<"operator"<<endl;
						buffer="";
						op_flag=0;
					}
				}
				
				
				else if(is_number(a))
				{cout<<"in number"<<endl;
					if(char_flag==0&&op_flag==0)
				     {
				     		num_flag=1;
					        buffer=buffer+a;
					 }
					 if (char_flag==1)
					 {
					 	buffer=buffer+a;
					 }
					 if(op_flag==1)
					 {
					 	    ofs<<buffer<<"--------->"<<"operator"<<endl;
						    op_flag=0;
						    buffer=a;
					 	
					 }
				}
				
				
				else if(is_operator(a))
				{
					if(num_flag==1)
					{
						ofs<<buffer<<"---------->"<<"num"<<endl;
						buffer=a;
						num_flag=0;
					}
					
					if(char_flag==1)
					{
						if(is_keyword(buffer))
						{
							ofs<<buffer<<"--------->"<<"keyword"<<endl;
							char_flag=0;
							buffer="";
						}
						else
						{
							ofs<<buffer<<"--------->"<<"identifier"<<endl;
						    char_flag=0;
						    buffer="";
						}
			     	}
			        
			        op_flag=1;
			        buffer=buffer+a;
			        cout<<"hi"<<buffer<<endl;
			     	
		    	}
			
			
				else if(is_char(a))
				{
					char_flag=1;
					if(num_flag==1)
					{
						buffer=buffer+a;
						ofs<<buffer<<"----------->"<<"error"<<endl;
						buffer="";
						num_flag=0;
					}
						if(op_flag==1)
					{
						ofs<<buffer<<"----------->"<<"operator"<<endl;
						buffer="";
						op_flag=0;
					}
					
					buffer=buffer+a;
				}
			}
	}
	
	ifs.close();
	ofs.close();
	
return 0;	
}
