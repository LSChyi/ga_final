#include <cstring>
#include <iostream>
#include "youbikeGa.h"
#include "chromosome.h"
#include "fitnessFunction.h"
#include <ctime>

#include <algorithm>
#include<vector>
#include<map>
#include<math.h>
using namespace std;

struct bike{
int fitness;
int* trans;
};

int* pop[20000];
bike youbike[20000];

YoubikeGa::YoubikeGa(int n_ell, int n_max_gen, int n_station_id,int population_size) {
    nfe = 0;
	ell = n_ell;
    max_gen = n_max_gen;
    station_id = n_station_id;
    generation = 0;
    fitnessFunction = new FitnessFunction(station_id);
	park = fitnessFunction->get_total();
    sample_f1 =new Chromosome(ell);
    sample_f2 =new Chromosome(ell);
    tn=10000;  
    n = population_size;
    generator_model = new double* [ell];
    for(int i = 0; i < n_ell; ++i) {
		generator_model[i] = new double [park*2+1];
		for(int i2 =0 ; i2 < park*2+1; i2++){
            generator_model[i][i2] = 0.5/double(park*2+1);
	    }
        generator_model[i][park] = 0.5;
    }
    best_fitness = std::numeric_limits<double>::infinity()*(-1);
    best_chromosome = new Chromosome(ell);
}

YoubikeGa::~YoubikeGa() {
    if(generator_model != NULL) {
        for(int i = 0; i < ell; ++i) {
            delete []generator_model[i];
        }

        delete []generator_model;
    }
}

bool YoubikeGa::should_terminate() {
	// generation >= max_gen
    if(generation >= max_gen)   
        return true;
    // all converge  , all > 0.999
    int temp = 0; 
    for (int i = 0 ; i < ell; i++){
		 bool check = true;
		 for (int i2 = 0 ;i2 < park*2+1 ; i2++){
		     if (generator_model[i][i2]>0.999){
			     check = false;
			     break;
			 }    
		  if(check)
		     temp++;
		 }			
	}
	if(temp == ell)
	  return true;
	  
    return false;
}

void YoubikeGa::run() {
        int* chromosome = new int[48];
        for(int i = 0; i < 48; ++i) {
            chromosome[i] = 0;
        }
        clock_t tStart = clock();
        double raw_fitness = fitnessFunction->get_fitness(chromosome, true, true);
        cout << "raw fitness: " << raw_fitness << endl;
        cout << "press enter to start optimization" << endl;
        cin.get();
        double fCost = (double)((clock()-tStart)*1000/CLOCKS_PER_SEC);
        cout << "call F cost: " << fCost << "ms" <<  endl;
        cout << "one Generation cost: " << fCost * 30 * 2/1000 << "s" << endl;
            
	while(!should_terminate()) {
		cout << endl <<  "Generation " << generation << endl;
        // 1. generate two chromosome
        srand (time(NULL)); // RAND
        int* sample_1;
        int* sample_2;
        int tournament = 30; 
        double best = -10000 ; 
        int* best_c; 
        while (tournament --)
        {
    	   sample_f1->sample(generator_model,park,sample_1);
           sample_f2->sample(generator_model,park,sample_2);
    	    // 2. ask fitness function
    	    double avg_fitness_1 = fitnessFunction->get_fitness(sample_1, true, false);
    	    nfe++;
    	    double avg_fitness_2 = fitnessFunction->get_fitness(sample_2, true, false);
            nfe++;
    	    if(avg_fitness_1>best)
                {
                   best =avg_fitness_1;
                   best_c = sample_1;  
                }
            if(avg_fitness_2>best)
            {
                best =avg_fitness_2;
                best_c = sample_2;  
            }
            // 3. update model
            if (avg_fitness_1 > avg_fitness_2){
                            for(int i = 0 ; i< ell ; i++){
    			   double update_value = 1.0/n;	
    			   if(generator_model[i][sample_2[i]+park]<update_value)	
    		              update_value = generator_model[i][sample_2[i]+park]; 
    			   generator_model[i][sample_2[i]+park]-= update_value; 	
    			   generator_model[i][sample_1[i]+park]+= update_value;
                              
    			 }
    	    }
            else if (avg_fitness_1 < avg_fitness_2){
                for(int i = 0 ; i< ell ; i++){
        		    double update_value = 1.0/n;	
        		    if(generator_model[i][sample_1[i]+park]<update_value)	
                        update_value = generator_model[i][sample_1[i]+park]; 
        	        generator_model[i][sample_1[i]+park]-= update_value; 	
        	        generator_model[i][sample_2[i]+park]+= update_value;
    	        }
            }
        }
        cout << "Best fitness : "<< best << endl;
        for(int i=0;i<ell;i++)
           cout<<best_c[i]<<' ';
        cout<<endl;
        // 4. generation += 1
        generation += 1;
        if(best > best_fitness) {
            best_fitness = best;
            best_chromosome->init(best_c);
        }
		
    }
    cout << "terminate" << endl;
	cout << "NFE = " << nfe << endl;
    cout << "best chromosome: ";
    best_chromosome->output();
    cout << "fitness: " << best_fitness << endl;
}

void YoubikeGa::output_model() {
    cout << "[" << endl;
    for(int i = 0; i < ell; ++i) {
        cout << "    " << "[ ";
        for(int j = 0; j < ell; ++j) {
            cout << generator_model[i][j] << " ";
        }
        cout << "    " << "]" << endl;
    }
    cout << "]" << endl;
}

////////////////// ecga  not sure can work ? ////////////////////



bool compare(bike a,bike b)
{
return a.fitness>b.fitness;	
}
char reff[10]={'0','1','2','3','4','5','6','7','8','9'};

double count_mdl(int* model,int l)
{
int ta;
double data=0;
map<string,int> mymap;
map<string,int>::iterator it;
for(int i=0;i<10000;i++)	
   {
	string t_s="";
	
	for(int i2=0;i2<l;i2++)
	   {
		ta = pop[i][model[i2]] ;
		int re = 0;
		string a="";
		while(1)
		    {
			 int y = ta %10;
			 a += reff[y];
			 ta /= 10 ;
			 re ++;
			 if(ta == 0)
			   break;
		    }
		for(int i3 = re-1;i3>-1;i3--)
		   t_s += a[i3];
		 t_s+="_";	
		}
it = mymap.find(t_s);
	if(it!= mymap.end())
	   mymap[t_s]++;
	else 
	  mymap[t_s]=1; 	
	  
	 
   }

for(it = mymap.begin();it != mymap.end();it++)
   {
	double b=double((*it).second) ;
	
	double ans =(b* log2(b/10000));
    data -= ans;			
   }
return data;
}

void YoubikeGa::ecga()
{


for(int i=0;i<tn;i++)
   {
    pop[i]=new int[ell];		
	//
	sample_f1->sample(generator_model,park,pop[i]);

	
   }	
 
for(int i=tn;i<2*tn;i++)
   pop[i]=new int[ell];

while(!should_terminate()) {
//initial
for(int i=0;i<tn;i++)
   {
	youbike[i].trans=pop[i];
	youbike[i].fitness= fitnessFunction->get_fitness(pop[i], true, false); 	
      
  }	
// model buiding	
vector<int> BB[48];
int BB_length[48];
double MDL;
double total_mdl=0;
bool able[48];
double each_mdl[48];  
for(int i=0;i<48;i++)	
   {
    BB_length[i]=1;		
	BB[i].push_back(i);
	int * ttt = new int[1];
	ttt[0]=i;
	able[i]=true;
	each_mdl[i]=count_mdl(ttt,1); 
	total_mdl+=each_mdl[i];
   }	
total_mdl += 48*log2(tn);   
// MDL	

MDL=total_mdl;
int record=0;
while (1)
{
double temp_mdl,tt;
double adapt;
int merge1,merge2;
for(int i=0;i<48;i++)
  {
   if(!able[i])
      continue;
   for(int i2=i+1;i2<48;i2++) 
      {
	  if(!able[i2])
	     continue;
	  int temp_l=BB_length[i]+BB_length[i2];
	  int* temp_model =new int [temp_l];
	  for(int j=0;j<BB_length[i];j++)
	     temp_model[j] = BB[i][j];
	  for(int j=BB_length[i];j<temp_l;j++)
	     temp_model[j] = BB[i2][j-BB_length[i]]; 
	  temp_mdl=count_mdl(temp_model,temp_l);
	  delete temp_model;
	  tt= total_mdl -each_mdl[i]-each_mdl[i2] + temp_mdl
	  - (pow(2,double(BB_length[i]))-1)*log2(tn) - (pow(2,double(BB_length[i2]))-1)*log2(tn) +(pow(2,double(temp_l))-1)*log2(tn);
	  if(MDL>tt)
	    {
		 MDL =tt;
		 adapt = temp_mdl;
		 merge1=i;
		 merge2=i2;
		}		
	  }	
   
  }
if (total_mdl ==MDL)
   break;
  
cout<<++record<<endl;
// merge

cout<<merge1<<' '<<merge2<<endl;
for(int i=0;i<BB_length[merge2];i++)
   BB[merge1].push_back(BB[merge2][i]);
each_mdl[merge1]=adapt;
BB_length[merge1]+=BB_length[merge2];/**/
total_mdl =MDL;
able[merge2]=false;
// print building blocks each time , can comment 
cout<<"building blocks update:"<<endl;
for(int i = 0; i<48;i++)
   {    
        if(!able[i])
          continue;
   	for(int i2=0;i2<BB_length[i];i2++)
	    cout<<BB[i][i2]<<' ';	
	cout<<endl; 	
	}
}

/// print building blocks each time , can comment 



//sample

for(int i=tn;i<2*tn;i++)
   {
    		
    //
	for(int j=0;j<48;j++)
	   {
	   if(!able[j])		
		  continue;
		 int a; 
			a=rand()%10000;
		for(int k=0;k<BB_length[j];k++)
			pop[i][BB[j][k]]=pop[a][BB[j][k]];	
	   }
	
	
	youbike[i].trans=pop[i];
	youbike[i].fitness= fitnessFunction->get_fitness(pop[i], true, false); 
        
   }	
// selection
selection();  /* */
cout<<"generation : "<<generation<<endl;
cout<<"best_fitness in this gerernation : ";
cout<<youbike[0].fitness<<endl;
cout<<"chromosome : ";
for(int i= 0 ;i<ell;i++)
   cout<<youbike[0].trans[i]<<' ';
cout<<endl;
if(best_fitness>youbike[0].fitness)
  {
   best_fitness=youbike[0].fitness;
   best_chromosome->init(youbike[0].trans);
  }
	generation+=1;
}	
}

void YoubikeGa::selection()
{
sort(youbike,youbike+tn+tn,compare);	
for(int i=0;i<tn;i++)
	for(int i2=0;i2<ell;i2++)
      pop[i][i2] = youbike[i].trans[i2];

}
