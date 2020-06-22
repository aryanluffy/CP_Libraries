class xorqtrie{
            public:
            struct node{
                int count=0;
                node* a[2]={NULL,NULL};
            };
            node *root;
            xorqtrie(){
                root=new node();
            }
            void insert(int val){
                int pos=29;
                node *temp=root;
                while(pos>-1){
                    if((1<<pos)&val){
                        if(temp->a[1]!=NULL){
                            temp->a[1]->count++;
                            temp=temp->a[1];
                        }
                        else{
                            temp->a[1]=new node();
                            temp->a[1]->count++;
                            temp=temp->a[1];
                        }
                    }
                    else{
                        if(temp->a[0]!=NULL){
                            temp=temp->a[0];
                            temp->count++;
                        }
                        else{
                            temp->a[0]=new node();
                            temp=temp->a[0];
                            temp->count++;
                        }
                    }
                    pos--;
                }
            }
            int minxorquery(int val){
                int pos=29;
                int ans=0;
                node *temp=root;
                while(pos>-1){
                    int x=((1<<pos)&val)!=0;
                    if(temp->a[x]!=NULL){
                        temp=temp->a[x];
                    }
                    else{
                        ans+=(1<<pos);
                        temp=temp->a[1-x];
                    }
                    pos--;
                }
                return ans;
            }
            void DELETE(int val){
                int pos=29;
                int ans=0;
                node*temp=root;
                while(pos>-1){
                    int x=((1<<pos)&val)!=0;
                    temp->a[x]->count--;
                    if(temp->a[x]->count==0){
                        temp->a[x]=NULL;
                        break;
                    }
                    temp=temp->a[x];
                    pos--;
                }
            }
        };
