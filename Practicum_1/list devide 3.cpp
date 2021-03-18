#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
struct node
{
    int date;
    struct node*next;
};
struct node* addhead(struct node*ph,int m)
{
    struct node* pt;
    if(pt=(struct node*)malloc(sizeof(struct node)))
    {
        pt->next=ph;
        pt->date=m;
        ph=pt;
        return ph;
    }
    printf("error\n");
    exit(-1);
}

struct node*addend(struct node*ph,int m)
{
    struct node*pt,*pl=ph;
    if(pt=(struct node*)malloc(sizeof(struct node)))
    {
        pt->next=NULL;
        pt->date=m;
    }
    else
    {
        printf("error\n");
        exit(-1);
    }
    if(ph==NULL)
        ph = pt;
    else
    {
        while(pl->next!=NULL)
            pl=pl->next;
        pl->next=pt;
    }
    return ph;
}


int main()
{
    struct node *p=NULL,*pl;
    int n,i,m;
    printf("input your numbers\n");
    scanf("%d",&n);
    if(n<=0)
    {
        printf("error\n");
        return 0;
    }
    for(i=0; i<n; i++)
    {
        scanf("%d",&m);
        if(m%3==0)
            p=addhead(p,m);
        else p=addend(p,m);
    }
    pl=p;
    while(pl)
    {
        printf("%d ",pl->date);
        pl=pl->next;
    }
    return 0;
}
