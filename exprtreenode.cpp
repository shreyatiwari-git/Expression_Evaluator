/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{
    type="";
    val=NULL;
    evaluated_value=NULL;
    left=NULL;
    right=NULL;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v)
{
    type=t;
    int* arr=new int(1);
    UnlimitedInt* u= new UnlimitedInt(arr, 2, 1, 1);
    val=new UnlimitedRational(v,u);
    evaluated_value=NULL;
    left=NULL;
    right=NULL;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v)
{
    type=t;
    UnlimitedInt* p=v->get_p();
    UnlimitedInt* q=v->get_q();
    if(p==NULL||q==NULL)
    {
        evaluated_value=NULL;
    }
    else
    {
        evaluated_value= new UnlimitedRational(p,q);
    }
    val=NULL;
    left=NULL;
    right=NULL;
    
}
ExprTreeNode::~ExprTreeNode()
{
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
}
