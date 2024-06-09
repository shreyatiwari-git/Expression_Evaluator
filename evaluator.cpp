/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

UnlimitedRational* evaluate(ExprTreeNode &root)
{
    if(root.left==NULL||root.right==NULL)
    {
        if(root.type=="VAR")
        {
            return root.evaluated_value;
        }
        else
        {
            return root.val;
        }
    }
    UnlimitedRational* lvalue= evaluate(*root.left);
    UnlimitedRational* rvalue= evaluate(*root.right);
    if(root.type=="ADD")
    {
       UnlimitedRational* res= UnlimitedRational::add(lvalue, rvalue);
        root.evaluated_value=res;
        return res;
    }
    if(root.type=="SUB")
    {
        UnlimitedRational* res= UnlimitedRational::sub(lvalue, rvalue);
        root.evaluated_value=res;
         return res;
    }
    if(root.type=="MUL")
    {
        UnlimitedRational* res= UnlimitedRational::mul(lvalue, rvalue);
        root.evaluated_value=res;
         return res;
    }
    if(root.type=="DIV")
    {
        UnlimitedRational* res= UnlimitedRational::div(lvalue, rvalue);
        root.evaluated_value=res;
         return res;
    }
    else
    {
        root.evaluated_value=NULL;
        return NULL;
    }
}


Evaluator::Evaluator()
{
    symtable=new SymbolTable();
}

Evaluator::~Evaluator()
{
    delete symtable;
}
void Evaluator::parse(vector<string> code)
{
    UnlimitedRational* temp=new UnlimitedRational(); // p / q
    ExprTreeNode* root=new ExprTreeNode(code[1],temp);
    root->left=new ExprTreeNode("VAR",temp);
    root->left->id=code[0];
    vector<ExprTreeNode*> stack;
    stack.push_back(root);
    for(int i=2;i<code.size();i++)
    {
        if(code[i]=="(")
        {
            ExprTreeNode* stor=new ExprTreeNode("",temp);
            stack.push_back(stor);
            stor=NULL;
        }
        else if(code[i]=="+"||code[i]=="-"||code[i]=="*"||code[i]=="/"||code[i]=="%")
        {
            if(code[i]=="+")
            {
                stack[stack.size()-1]->type="ADD";
            }
            if(code[i]=="-")
            {
                stack[stack.size()-1]->type="SUB";
            }
            if(code[i]=="*")
            {
                stack[stack.size()-1]->type="MUL";
            }
            if(code[i]=="/")
            {
                stack[stack.size()-1]->type="DIV";
            }
            if(code[i]=="%")
            {
                stack[stack.size()-1]->type="MOD";
            }
            
        }
        else if(code[i]==")")
        {
            ExprTreeNode* top=stack[stack.size()-1];
            stack.pop_back();
            if( stack[stack.size()-1]->left==NULL)
            {
                stack[stack.size()-1]->left=top;
            }
            else
            {
                stack[stack.size()-1]->right=top;
            }
            top=NULL;
        }
        else
        {
            string typ;
            if(code[i][0]=='-'||code[i][0]=='1'||code[i][0]=='2'||code[i][0]=='3'||code[i][0]=='4'||code[i][0]=='5'||code[i][0]=='6'||code[i][0]=='7'||code[i][0]=='8'||code[i][0]=='9'||code[i][0]=='0')
            {
                typ="VAL";
            }
            else
            {
                typ="VAR";
            }
            if( stack[stack.size()-1]->left==NULL)
            {
                if(typ=="VAL")
                {
                    UnlimitedInt* valu=new UnlimitedInt(code[i]);
                    stack[stack.size()-1]->left=new ExprTreeNode(typ,valu);
                }
                else
                {
                    UnlimitedRational* valu=symtable->search(code[i]);
                    stack[stack.size()-1]->left=new ExprTreeNode(typ,valu);
                    stack[stack.size()-1]->left->id=code[i];
                }
            }
            else
            {
                if(typ=="VAL")
                {
                    UnlimitedInt* valu=new UnlimitedInt(code[i]);
                    stack[stack.size()-1]->right=new ExprTreeNode(typ,valu);
                }
                else
                {
                    UnlimitedRational* valu=symtable->search(code[i]);
                    stack[stack.size()-1]->right=new ExprTreeNode(typ,valu);
                    stack[stack.size()-1]->right->id=code[i];
                }
            }
        }
    }
    stack.pop_back();
    expr_trees.push_back(root);
    root=NULL;
}

void Evaluator::eval()
{
    ExprTreeNode* exp=expr_trees[expr_trees.size()-1];
    UnlimitedRational* res= evaluate(*exp->right);
    symtable->insert(exp->left->id,res);
    exp->left->evaluated_value=res;
    exp=NULL;
}





