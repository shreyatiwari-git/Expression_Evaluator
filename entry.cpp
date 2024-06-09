/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry()
{
    key="";
    val=NULL;
    left=NULL;
    right=NULL;
}

SymEntry::SymEntry(string k, UnlimitedRational* v)
{
    key=k;
    UnlimitedInt* p=v->get_p();
    UnlimitedInt* q=v->get_q();
    val= new UnlimitedRational(p,q);
    left=NULL;
    right=NULL;
}

SymEntry::~SymEntry()
{
    delete val;
    delete left;
    delete right;
}
