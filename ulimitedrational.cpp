/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedRational::UnlimitedRational()
{
    p=NULL;
    q=NULL;
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den)
{
    if(den->get_size()==1&&den->get_array()[0]==0)
    {
        int* temp=new int(0);
        p= new UnlimitedInt(temp,2,1,1);
        q= new UnlimitedInt(temp,2,1,1);
        return;
    }
    UnlimitedInt* temp_hcf=UnlimitedInt::mod(num,den);
    if(temp_hcf->get_size()==1&&temp_hcf->get_array()[0]==0)
    {
        delete temp_hcf;
        temp_hcf=new UnlimitedInt(den->get_array(),den->get_capacity(),den->get_sign(),den->get_size());
    }
    else
    {
        UnlimitedInt* temp_hcf2=UnlimitedInt::mod(den,temp_hcf);
        if(temp_hcf2->get_size()==1&&temp_hcf2->get_array()[0]==0)
        {
            delete temp_hcf2;
        }
        else
        {
            while(1)
            {
                UnlimitedInt* temp;
                temp=UnlimitedInt::mod(temp_hcf,temp_hcf2);
                if(temp->get_size()==1&&temp->get_array()[0]==0)
                {
                    delete temp_hcf;
                    temp_hcf=temp_hcf2;
                    temp_hcf2=NULL;
                    break;
                }
                delete temp_hcf;
                temp_hcf=temp_hcf2;
                temp_hcf2=temp;
                temp=NULL;
            }
        }
    }
    p= p->div(num,temp_hcf);
    q= q->div(den,temp_hcf);
    return;
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational:: get_p()
{
    return p;
}

UnlimitedInt* UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str() // Return the numerator as a string
{
    return p->to_string();
}

string UnlimitedRational::get_q_str() // Return the denominator as a string
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str() // Return the rational as "p/q"
{
    string s;
    s=p->to_string()+"/"+q->to_string();
    return s;
}
// Rational arithmetic operations
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt* num=UnlimitedInt::add(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i1->q, i2->p));
    UnlimitedInt* den= UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedRational* u=new UnlimitedRational(num,den);
    return u;
}
UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt* num=UnlimitedInt::sub(UnlimitedInt::mul(i1->p, i2->q), UnlimitedInt::mul(i1->q, i2->p));
    UnlimitedInt* den= UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedRational* u=new UnlimitedRational(num,den);
    return u;
}
UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt* num=UnlimitedInt::mul(i1->p,i2->p);
    UnlimitedInt* den= UnlimitedInt::mul(i1->q,i2->q);
    UnlimitedRational* u=new UnlimitedRational(num,den);
    return u;
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedInt* num=UnlimitedInt::mul(i1->p,i2->q);
    UnlimitedInt* den= UnlimitedInt::mul(i1->q,i2->p);
    UnlimitedRational* u=new UnlimitedRational(num,den);
    return u;
}
