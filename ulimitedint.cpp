/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

#include "ulimitedint.h"


UnlimitedInt::UnlimitedInt()
{
    size=0;
    sign=1;
    capacity=16;
    unlimited_int=NULL;
}

UnlimitedInt::UnlimitedInt(string s)
{
    if(s[0]=='-')
    {
        size=(int)s.size()-1;
        sign=-1;
        capacity=size*2;
        unlimited_int=new int[capacity];
        for(int i=0,j=size;i<size;i++,j--)
        {
            unlimited_int[i]=(s[j]-'0');
        }
    }
    else
    {
        size=(int)s.size();
        sign=1;
        capacity=size*2;
        unlimited_int=new int[capacity];
        for(int i=0,j=size-1;i<size;i++,j--)
        {
            unlimited_int[i]=(s[j]-'0');
        }
    }
}

UnlimitedInt::UnlimitedInt(int i)
{
    if(i<0)
    {
        sign=-1;
        i=i*-1;
    }
    else
    {
        sign=1;
    }
    int j=i;
    int count=0;
    while(i>0)
    {
        i=i/10;
        count++;
    }
    size=count;
    if(size==0)
    {
        size++;
    }
    capacity=size*2;
    unlimited_int=new int[capacity];
    for(int i=0;i<size;i++)
    {
        unlimited_int[i]=j%10;
        j=j/10;
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz)
{
    size=sz;
    sign=sgn;
    capacity=cap;
    unlimited_int=new int[capacity];
    for(int i=0;i<size;i++)
    {
        unlimited_int[i]=ulimited_int[i];
    }

}

UnlimitedInt::~UnlimitedInt()
{
    delete []unlimited_int;
}


int UnlimitedInt:: get_size()
{
    return size;
}

int* UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

 UnlimitedInt* UnlimitedInt:: add(UnlimitedInt* i1, UnlimitedInt* i2)
{
     int s1=i1->get_size();
     int s2=i2->get_size();
     int sgn;
     int greater=0,size;
     if(s1>s2) { greater=1; size=s1; }
     else if(s2>s1) { greater=2; size=s2; }
     else
     {
         int check=s1-1;
         size=s1;
         while(check>=0)
         {
             if(i1->unlimited_int[check]>i2->unlimited_int[check])
             {
                 greater=1;
                 break;
             }
             else if(i1->unlimited_int[check]<i2->unlimited_int[check])
             {
                 greater=2;
                 break;
             }
             else { check--;}
         }
     }
     int* arr=new int[size+1];
     if(i1->get_sign()*i2->get_sign()>0)
     {
         sgn=i1->get_sign();
        int  counter1=0,counter2=0,carry=0,sum=0;
         while(counter1<s1&&counter2<s2)
         {
             sum=i1->unlimited_int[counter1]+i2->unlimited_int[counter2]+carry;
             arr[counter1]=sum%10;
             carry=sum/10;
             counter1++; counter2++;
         }
         while(counter1<s1)
         {
             sum=i1->unlimited_int[counter1]+carry;
             arr[counter1]=sum%10;
             carry=sum/10;
             counter1++;
         }
         while(counter2<s2)
         {
             sum=i2->unlimited_int[counter2]+carry;
             arr[counter2]=sum%10;
             carry=sum/10;
             counter2++;
         }
         if(carry!=0)
         {
             arr[size++]=carry;
         }
     }
     else
     {
         int  counter1=0,counter2=0,carry=0,diff=0;
         if(greater==0)
         {
             size=1;
             sgn=1;
             arr[0]=0;
         }
         else
         {
             if (greater==1)
             {
                 sgn=i1->get_sign();
                 while(counter2<s2)
                 {
                     diff=i1->unlimited_int[counter1]-i2->unlimited_int[counter2]-carry;
                     if(diff<0)
                     {
                         arr[counter2]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter2]=diff;
                         carry=0;
                     }
                     counter1++; counter2++;
                 }
                 while(counter1<s1)
                 {
                     diff=i1->unlimited_int[counter1]-carry;
                     if(diff<0)
                     {
                         arr[counter1]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter1]=diff;
                         carry=0;
                     }
                     counter1++;
                 }
                 
             }
             else
             {
                 sgn=i2->get_sign();
                 while(counter1<s1)
                 {
                     diff=i2->unlimited_int[counter2]-i1->unlimited_int[counter1]-carry;
                     if(diff<0)
                     {
                         arr[counter1]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter1]=diff;
                         carry=0;
                     }
                     counter1++; counter2++;
                 }
                 while(counter2<s2)
                 {
                     diff=i2->unlimited_int[counter2]-carry;
                     if(diff<0)
                     {
                         arr[counter2]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter2]=diff;
                         carry=0;
                     }
                     counter2++;
                 }
                 
             }
            while(arr[size-1]==0)
            {
                size--;
            }
             
         }
     }
     UnlimitedInt* u=new UnlimitedInt(arr,size*2,sgn,size);
     return u;
}

 UnlimitedInt* UnlimitedInt:: sub(UnlimitedInt* i1, UnlimitedInt* i2)
{
     int sgn1=i1->get_sign(),sgn2=-1*i2->get_sign();
     int s1=i1->get_size();
     int s2=i2->get_size();
     int sgn;
     int greater=0,size;
     if(s1>s2) { greater=1; size=s1; }
     else if(s2>s1) { greater=2; size=s2; }
     else
     {
         int check=s1-1;
         size=s1;
         while(check>=0)
         {
             if(i1->unlimited_int[check]>i2->unlimited_int[check])
             {
                 greater=1;
                 break;
             }
             else if(i1->unlimited_int[check]<i2->unlimited_int[check])
             {
                 greater=2;
                 break;
             }
             else { check--;}
         }
     }
     int* arr=new int[size+1];
     if(sgn1*sgn2>0)
     {
         sgn=sgn1;
        int  counter1=0,counter2=0,carry=0,sum=0;
         while(counter1<s1&&counter2<s2)
         {
             sum=i1->unlimited_int[counter1]+i2->unlimited_int[counter2]+carry;
             arr[counter1]=sum%10;
             carry=sum/10;
             counter1++; counter2++;
         }
         while(counter1<s1)
         {
             sum=i1->unlimited_int[counter1]+carry;
             arr[counter1]=sum%10;
             carry=sum/10;
             counter1++;
         }
         while(counter2<s2)
         {
             sum=i2->unlimited_int[counter2]+carry;
             arr[counter2]=sum%10;
             carry=sum/10;
             counter2++;
         }
         if(carry!=0)
         {
             arr[size++]=carry;
         }
     }
     else
     {
         int  counter1=0,counter2=0,carry=0,diff=0;
         if(greater==0)
         {
             size=1;
             sgn=1;
             arr[0]=0;
         }
         else
         {
             if (greater==1)
             {
                 sgn=sgn1;
                 while(counter2<s2)
                 {
                     diff=i1->unlimited_int[counter1]-i2->unlimited_int[counter2]-carry;
                     if(diff<0)
                     {
                         arr[counter2]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter2]=diff;
                         carry=0;
                     }
                     counter1++; counter2++;
                 }
                 while(counter1<s1)
                 {
                     diff=i1->unlimited_int[counter1]-carry;
                     if(diff<0)
                     {
                         arr[counter1]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter1]=diff;
                         carry=0;
                     }
                     counter1++;
                 }
                 
             }
             else
             {
                 sgn=sgn2;
                 while(counter1<s1)
                 {
                     diff=i2->unlimited_int[counter2]-i1->unlimited_int[counter1]-carry;
                     if(diff<0)
                     {
                         arr[counter1]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter1]=diff;
                         carry=0;
                     }
                     counter1++; counter2++;
                 }
                 while(counter2<s2)
                 {
                     diff=i2->unlimited_int[counter2]-carry;
                     if(diff<0)
                     {
                         arr[counter2]=diff+10;
                         carry=1;
                     }
                     else
                     {
                         arr[counter2]=diff;
                         carry=0;
                     }
                     counter2++;
                 }
                 
             }
            while(arr[size-1]==0)
            {
                size--;
            }
             
         }
     }
     UnlimitedInt* u=new UnlimitedInt(arr,size*2,sgn,size);
     return u;
}

UnlimitedInt* UnlimitedInt:: mul(UnlimitedInt* i1, UnlimitedInt* i2)
{
    if((i2->get_size()==1&&i2->unlimited_int[0]==0)||(i1->get_size()==1&&i1->unlimited_int[0]==0))
    {
        int* temp=new int(0);
        UnlimitedInt* u=new UnlimitedInt(temp,2,1,1);
        return u;
        
    }
    int s1=i1->get_size();
    int s2=i2->get_size();
    int sgn=i1->get_sign()*i2->get_sign();
    int size=s1+s2;
    int* arr=new int[size];
    for(int i=0;i<size;i++)
    {
        arr[i]=0;
    }
        for(int i=0;i<s2;i++)
        {
            for(int j=0;j<s1;j++)
            {
                arr[j+i]=arr[i+j]+i1->unlimited_int[j]*i2->unlimited_int[i];
            }
            
        }
        int trav=0;
        int carry=0;
        while(trav<size)
        {
            arr[trav]=arr[trav]+carry;
            carry=arr[trav]/10;
            arr[trav]=arr[trav]%10;
            trav++;
        }
        while(arr[size-1]==0&&size>1)
        {
            size--;
        }
    UnlimitedInt* u=new UnlimitedInt(arr,size*2,sgn,size);
    return u;
}

 UnlimitedInt* UnlimitedInt:: div(UnlimitedInt* i1, UnlimitedInt* i2)
{
     int counter=0;
     string s,res;
     if (i1->get_sign()*i2->get_sign()>0)
     {
        s="";
        res="";
     }
     else
     {
         s="-";
         res="-";
     }
     UnlimitedInt* div=new UnlimitedInt[10];
     for(int i=0;i<10;i++)
     {
         int* in=new int(i);
         UnlimitedInt* multiplier=new UnlimitedInt(in,1,1,1);
         div[i]=*mul(i2,multiplier);
     }
     UnlimitedInt* dividend= new UnlimitedInt(i1->get_array(),i1->get_capacity(),i1->get_sign(),i1->get_size());
    int  s1=i1->get_size();
   int   s2=i2->get_size();
     int size_diff=s1-s2+1;
     int s_2=s2;
     while(s1>=s2&&counter<size_diff)
     {
         counter++;
         int divisor=0,greater=0,i;
         for( i=0;i<10&&greater==0;i++)
         {
                         int s_1=div[i].get_size();
                         if(s_1>s_2) { greater=1;divisor=i;break;}
                         else if(s_2>s_1)
                         {
                                 int check=s_1-1;
                                 int check2=s1-1;
                             if(dividend->unlimited_int[check2]!=0)
                             {
                                 greater=0;continue;
                             }
                             else
                             {
                                 check2--;
                                 while(check>=0)
                                 {
                                     if(dividend->unlimited_int[check2]>div[i].unlimited_int[check])
                                     {
                                         greater=0;
                                         break;
                                     }
                                     else if(dividend->unlimited_int[check2]<div[i].unlimited_int[check])
                                     {
                                         greater=1;divisor=i; break;
                                     }
                                     else { check--;check2--;}
                                 }
                                 if(greater==1)
                                 {
                                     i--;
                                 }
                                 if(check==-1)
                                 {
                                     greater=1;divisor=i;i++;break;
                                 }
                             }
                         }
                         else
                         {
                             int check=s_1-1;
                             int check2=s1-1;
                             while(check>=0)
                             {
                                 if(dividend->unlimited_int[check2]>div[i].unlimited_int[check])
                                 {
                                     greater=0;break;
                                 }
                                 else if(dividend->unlimited_int[check2]<div[i].unlimited_int[check])
                                 {
                                     greater=1;divisor=i; break;
                                 }
                                 else { check--;check2--;}
                             }
                             if(greater==1)
                             {
                                 i--;
                             }
                             if(check==-1)
                             {
                                 greater=1;divisor=i;i++;break;
                             }
                         }
         }
         i--;
         s=s+(char)(i+'0');
         int sz1=div[i].get_size(),carry=0;
         for(int j=0;j<sz1;j++)
         {
             int diff= dividend->unlimited_int[s1-s_2+j]-div[i].unlimited_int[j]-carry;
             if(diff<0)
             {
                 diff=diff+10;
                 carry=1;
             }
             else
             {
                 carry=0;
             }
             dividend->unlimited_int[s1-s_2+j]=diff;
         }
         if(carry==1)
         {
             dividend->unlimited_int[s1-s_2+sz1]=dividend->unlimited_int[s1-s_2+sz1]-1;
             carry=0;
         }
         if(dividend->unlimited_int[s1-1]==0)
         {
             s1--;
         }
         else
         {
             s_2++;
         }
            
     }
     int i=0;
     while(s[i]=='0'||s[i]=='-')
     {
         i++;
     }
     for(int j=i;j<s.size();j++)
     {
         res=res+s[j];
     }
     if(res==""||res=="-")
     {
         res="0";
     }
     UnlimitedInt* u= new UnlimitedInt(res);
     return u;
}

UnlimitedInt* UnlimitedInt:: mod(UnlimitedInt* i1, UnlimitedInt* i2)
{
    int counter=0;
    int sgn;
    if (i1->get_sign()*i2->get_sign()>0)
    {
        sgn=1;
    }
    else
    {
        sgn=-1;
    }
    UnlimitedInt* div=new UnlimitedInt[10];
    for(int i=0;i<10;i++)
    {
        int* in=new int(i);
        UnlimitedInt* multiplier=new UnlimitedInt(in,1,1,1);
        div[i]=*mul(i2,multiplier);
    }
    UnlimitedInt* dividend= new UnlimitedInt(i1->get_array(),i1->get_capacity(),i1->get_sign(),i1->get_size());
   int  s1=i1->get_size();
  int   s2=i2->get_size();
    int size_diff=s1-s2+1;
    int s_2=s2;
    while(s1>=s2&&counter<size_diff)
    {
        counter++;
        int divisor=0,greater=0,i;
        for( i=0;i<10&&greater==0;i++)
        {
                        int s_1=div[i].get_size();
                        if(s_1>s_2) { greater=1;divisor=i;break;}
                        else if(s_2>s_1)
                        {
                                int check=s_1-1;
                                int check2=s1-1;
                            if(dividend->unlimited_int[check2]!=0)
                            {
                                greater=0;continue;
                            }
                            else
                            {
                                check2--;
                                while(check>=0)
                                {
                                    if(dividend->unlimited_int[check2]>div[i].unlimited_int[check])
                                    {
                                        greater=0;
                                        break;
                                    }
                                    else if(dividend->unlimited_int[check2]<div[i].unlimited_int[check])
                                    {
                                        greater=1;divisor=i; break;
                                    }
                                    else { check--;check2--;}
                                }
                                if(greater==1)
                                {
                                    i--;
                                }
                                if(check==-1)
                                {
                                    greater=1;divisor=i;i++;break;
                                }
                            }
                        }
                        else
                        {
                            int check=s_1-1;
                            int check2=s1-1;
                            while(check>=0)
                            {
                                if(dividend->unlimited_int[check2]>div[i].unlimited_int[check])
                                {
                                    greater=0;break;
                                }
                                else if(dividend->unlimited_int[check2]<div[i].unlimited_int[check])
                                {
                                    greater=1;divisor=i; break;
                                }
                                else { check--;check2--;}
                            }
                            if(greater==1)
                            {
                                i--;
                            }
                            if(check==-1)
                            {
                                greater=1;divisor=i;i++;break;
                            }
                        }
            
        }
        i--;
        int sz1=div[i].get_size(),carry=0;
        for(int j=0;j<sz1;j++)
        {
            int diff= dividend->unlimited_int[s1-s_2+j]-div[i].unlimited_int[j]-carry;
            if(diff<0)
            {
                diff=diff+10;
                carry=1;
            }
            else
            {
                carry=0;
            }
            dividend->unlimited_int[s1-s_2+j]=diff;
        }
        if(carry==1)
        {
            dividend->unlimited_int[s1-s_2+sz1]=dividend->unlimited_int[s1-s_2+sz1]-1;
            carry=0;
        }
        if(dividend->unlimited_int[s1-1]==0)
        {
            s1--;
        }
        else
        {
            s_2++;
        }
           
    }
    while(dividend->unlimited_int[s1-1]==0&&s1>0)
    {
        s1--;
    }
    if(s1==0)
    {
        s1=1;
    }
    UnlimitedInt* u= new UnlimitedInt(dividend->unlimited_int,s1*2,sgn,s1);
    return u;
}

string UnlimitedInt::to_string()
{
    string s="";
    if(sign==-1)
    {
        s="-";
    }
    for(int i=size-1;i>=0;i--)
    {
        s+=(char)(unlimited_int[i]+'0');
    }
    return s;
}
int main()
{
    UnlimitedInt* a1=new UnlimitedInt(500);
    UnlimitedInt* a2=new UnlimitedInt(0);
    UnlimitedInt* a3=UnlimitedInt::div(a1, a2);
    cout<<a3->to_string();
}
