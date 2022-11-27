#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<vector>
using namespace std;


#define PRINT_VECTOR(a) cout << " vector: " << endl ; for (auto k = a.begin(); k != a.end(); k++) cout << *k << endl
#define PRINT_V_V(a) cout << " V_V " << endl ; for (auto k = a.begin(); k != a.end(); k++) { for (auto x : *k) cout << x << endl; }
#define VECTOR_D(b) vector<double> b
class Mesh{
    private:
    vector<vector<double> > vert, face;
    string fileName;
    
    public:
    
    Mesh(string name): fileName(name) 
    { 
        char firstLetter;
        double x, y, z; 
        vector<double> v1, f1; 
        ifstream inFil(fileName); 
        
        while (inFil)
        {
            
            inFil >> firstLetter;
            if (firstLetter == 'v')
                {inFil >> x >> y >> z ; 
                v1.push_back(x); v1.push_back(y); v1.push_back(z);
                vert.push_back(v1);
                v1.pop_back(); v1.pop_back(); v1.pop_back();
                
                }
        }
    }

    
    vector<double> get_dimensions(){
        vector<double> dimensionVec;
       
        vector<vector<double> > results;
        results = getMaxMin(3);

        dimensionVec.push_back(abs(results[0][0] - results[1][0]));
        dimensionVec.push_back(abs(results[0][1] - results[1][1]));
        dimensionVec.push_back(abs(results[0][2] - results[1][2]));
        
         
        return dimensionVec ;
    }

        
    vector<vector<double> > getMaxMin(int numD){
        
        vector<vector<double> > results;
        vector<double> resultMax, resultMin;
        for (int z = 0; z < numD; z++){ 

        double m = vert[0][z]; // initialize the maximum to be value of column z in first row.
        for(int i = 1; i < vert.size(); i++)
            { m = max(m, vert[i][z]);}
            
        resultMax.push_back(m); 
            
        double n = vert[0][z]; // initialize the maximum to be value of column z in first row.
        for(int j = 1; j < vert.size(); j++)
            {n = min(n, vert[j][z]); }
          
        resultMin.push_back(n);
        }  
        
        results.push_back(resultMax); 
        results.push_back(resultMin); 
        
        
        return results;
    
    }

    };



int main(int argc, char **argv){

    string filename;
   
    //***********
    vector<double> volume;  /* new code */
    vector<string> names;    /* new code */
    vector<double> volumeCopy; /* new code */
    vector<double> namesCopy; /* new code */
    vector<double> temp;
    int count = 0, countForLoop=0;
    //***********
    vector<vector<double> > result;
    if (argc > 1) { 
        for (int i = 1; i< argc ; i++) {        
            filename = argv[i];

    names.push_back(filename); /* new code */
    
    Mesh mesh1(filename);

    VECTOR_D(temp); temp = mesh1.get_dimensions();
   // PRINT_VECTOR(temp);
    result.push_back(temp);
   
   // PRINT_V_V(result);

    volume.push_back(result[countForLoop][0] * result[countForLoop][1] * result[countForLoop][2]); 
    //PRINT_VECTOR(volume) ;
    countForLoop++;

}
    volumeCopy = volume;  // original unsorted volumes correspond to the string filename order
    sort(volume.begin(), volume.end(), greater<double>()); // descending order of volumes
    for (double x : volume)
{
        auto it = find(volumeCopy.begin(), volumeCopy.end(), x);
        cout << volume[count] << " " << names[it - volumeCopy.begin()] << " " <<  result[count][0] << " " << result[count][1] << " " << result[count][2] << endl;
        count++;
}

return 0;

}
}