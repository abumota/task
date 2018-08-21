#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <math.h>
#include <iomanip>
using namespace std;


float print_the_equation(string& s);
//you added & here be carfull
string get_constant(string the_equation);
float turn_string_to_flaot( string& s);
string turn_float_to_srting(float f);
string find_coffcient_of_repeated( int x, string& the_equation,int& the_start);
//ask about call by refrence for vector
void print_the_coff(string& s,vector<string> v,int n);
bool true_or_false(string& s, string& varia , int index_of_re);
void add(set<string> name_of_variables,string& equ1,string& equ2);
void subtract(set<string> name_of_variables,string& equ1,string& equ2);
float float_constant(string& equ);
void subtract_for_substitute(set<string> name_of_variables,string& equ1,string& equ2,string& varia);
void display_the_d(set<string> name_of_variables,vector<string> v);
void display_the_d_of_var(set<string> name_of_variables,vector<string> v,string vari );
float get_the_dete(set<string> name_of_variables,vector<string> v,string vari );
//float determinantOfMatrix( vector<vector<float> >num , int n);
//void getCofactor(vector<vector<float> >num , vector<vector<float> > temp, int p, int q, int n);
float determinantOfMatrix(float mat[100][100], int n);
void getCofactor(float mat[100][100], float temp[100][100], int p, int q, int n);

class var
{


private:
	string nameof;
	vector<string> coff;
	vector<float> coffn;
public:
	

};




int main()
{
	int n,index1=0,index2=0;

	string s,varia,v_complete;
	set<string> name_of_variables;
	cin>>n;
	vector<string> v,l;
	map <string,string> the_collector;
	map<string,string> ::iterator itr;
	for (int i = 0; i < n; i++)
	{
		cin>>s;
		v.push_back(s);
	}
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < v[i].length(); j++)
		{
			// get the variable name and the index of (=)
			int index_of_equal = v[i].find("="); 
			if ( isalpha(v[i][j]))
			{
				index1=j;
				for (int k = j+1; k < v[i].length(); k++)
				{
					//beawre from last or
					if ( v[i][k] == '+' || v[i][k] == '-' || v[i][k] == '=' || k==(v[i].length())-1)
					{
						index2=k;
						// you might remove the below line it is a bug maybe because the lenght change when you make erase 
						break;
					}
				}
			}
			else
			{
				continue;
			}

			//store the variable in a set name_of_variables

			if (index2 == v[i].length()-1)	
			 varia = v[i].substr(index1,(index2-index1)+1);
			else
			 varia = v[i].substr(index1,index2-index1);

			if (varia != "")
			name_of_variables.insert(varia);
			string coffcients_of_equation="";
			//get the coffecients
			// the delete index 
			int delete_index_start=0;
			// sign of the coffcients
			string sign ;
			// case example x1+2x2=5 the coffceient is 1 of x1
			if ( index1-1 == -1)
			{
				delete_index_start =index1; 
				coffcients_of_equation="1";
			}
			// case example 5x1+x2=0 the coffcient is 1 for x2
			else if ( v[i][index1-1] == '+' ) 
			{
				// the delete start
				delete_index_start = index1-1;
				//check if before the =
				if ( index1 < index_of_equal )
				{
					coffcients_of_equation = "1";
				}
				else
				{
					coffcients_of_equation = "-1";
				}
			}
			//case xample 5x1-x2=0 the coffcint is -1 for x2
			else if ( v[i][index1-1] == '-')
			{
				delete_index_start =index1-1; 
				// check if before the = 
				if (index1 < index_of_equal)
				{
					coffcients_of_equation ="-1";
				}
				else
				{
					coffcients_of_equation = "1";
				}
			}
			// case example 5x1=x2-5
			else if ( v[i][index1-1] == '=')
			{
				delete_index_start =index1; 
				coffcients_of_equation = "-1";
			}
			else 
			{
				// case of example genearl case with float and more than on digit coffcients
			for (int p = index1-1; p >= 0; p--)
			{

				if (v[i][p] != '+' && v[i][p] != '-' && v[i][p] != '=' )
				{
					coffcients_of_equation.insert(0,1,v[i][p]);
				}
				// when it reaches + 
				else if ( v[i][p] == '+' )
				{
					// check before =
					if ( p < index_of_equal)
					{
					delete_index_start=p;
					break;
					}
					else
					{
						coffcients_of_equation.insert(0,"-");
						delete_index_start=p;
					     break;
					}
				}
				//when it reaches -
				else if( v[i][p] == '-')
				{
					//check if brfore =
					if ( p < index_of_equal)
					{
					coffcients_of_equation.insert(0,"-");
					delete_index_start=p;
					break;
					}
					else
					{
						delete_index_start=p;
						break;
					}
				
				}
				// when it reaches =
				else if (v[i][p] == '=')
				{
					delete_index_start=p+1;
					break;
				}

			   }
			// end of coffcient get function
			

			}
			// turn the value of coffcient from string to float
			float value_of_string = turn_string_to_flaot(coffcients_of_equation);
             
			// continue here
			// find if the variable is reapeted
			// the index of reapted variavle 
			int index_of_re=0;

			// important change here 


			if ( index2 == v[i].length()-1)
				v[i].erase(delete_index_start,(index2-delete_index_start)+1);
			else 
				v[i].erase(delete_index_start,index2-delete_index_start);


			// important change above



			// you have to set j as 0; be carful
			j=0;
			
			while (true)
			{
				index_of_re = v[i].find(varia);



				// be carful from this case x1+x2+x12=5 it will delete x12 fix this bug 



				if ( index_of_re != -1 && true_or_false(v[i],varia,index_of_re))
				{


					//function that does take v[i] and index_of_re and delete-index and returns a string and change the delete_index
					coffcients_of_equation = find_coffcient_of_repeated(index_of_re,v[i],delete_index_start);
					// after you get he string coff you turn it to float and add the previous value
					
						value_of_string += turn_string_to_flaot(coffcients_of_equation);
					// then you erase it from existance (the repeted variable )
						int index2_of_re= index_of_re + varia.length();

						// important change 
						if ( index2_of_re== v[i].length()-1)
							v[i].erase(delete_index_start,(index2_of_re-delete_index_start)+1);
						else
							v[i].erase(delete_index_start,index2_of_re-delete_index_start);
					// becarful from j=0
					j=0;
				}
				else
				{
					break;
				}

			}
			// continue here 
			// the case that the coffcients eliminate each other x1-x1=0
			if ( value_of_string == 0)
			{
				//maybe bug here continue rather than break
				continue;
			}
			// use the map (the_collector to save values);
			the_collector.insert(pair <string,string> (varia,turn_float_to_srting(value_of_string)));
		// the end of loop j
		}
		//start from hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
		// you should make another loop after this this j loop to catch constants
		// after finishing the equation  loop and into loop i 
		// get the string of cons of equation i
		string the_constant = get_constant(v[i]);
		//test line

	//	cout<<the_constant<<endl;


		

		
		for (itr = the_collector.begin(); itr != the_collector.end() ; itr++)
		{
			if ( itr != the_collector.begin() )
		{
			if ( turn_string_to_flaot(itr->second) > 0 )
			{
				v_complete +="+"+itr->second+itr->first;
			//	cout<<"+"<<itr->second<<itr->first;
			}
			else
			{
				v_complete +=itr->second+itr->first;
			//	cout<<itr->second<<itr->first;
			}
			
		}
			else
			{
				v_complete +=itr->second+itr->first; 
			//	cout<<itr->second<<itr->first;
	
			}
		}
		v_complete +="="+the_constant;
		v[i] = v_complete;
		v_complete = "";
		// the erase line of the map
		 //cout<<endl;
		the_collector.erase(the_collector.begin(),the_collector.end());
	//	cout<<v[i]<<endl;

		
	}
	// end of for loops i 
	// command line operation
	string command="";
	// what the fuckkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
	cin.ignore();
	 getline(cin,command);
	while ( command != "quit")
	{
		
		//getline(cin,command);
		// print num_of_variables
		if ( command =="num_vars")
		{
			 cout<<name_of_variables.size()<<endl;
		}
		else if ( command.compare(0,8,"equation i",0,8) == 0)
		{
			// fix this shit code later man
			string the_equ = command.substr(9,3);
			float the_float = turn_string_to_flaot(the_equ);
			int the_int = (int)the_float;
			cout<<v[the_int-1]<<endl;
			// dont forget to fix it okkkkkkkkkkkkkkkkkkkkkkkkkkkkk is is headious 
		}
		else if ( command.compare(0,6,"column",0,6) == 0)
		{

			// a bug here doesnt return 0 if the variable doesnt exist 

			print_the_coff(command,v,n);
		
		}
		else if (command.compare(0,3,"add",0,3) == 0)
		{
			string temp;
			stringstream the_num;
			int equ1=0,equ2=0;
			the_num<<command;
			the_num>>temp;
			the_num>>equ1;
			the_num>>equ2;
			add(name_of_variables,v[equ1-1],v[equ2-1]);

		}
		else if ( command.compare(0,8,"subtract",0,8) == 0)
		{

			string temp1;
			stringstream the_num1;
			int equ11=0,equ22=0;
			the_num1<<command;
			the_num1>>temp1;
			the_num1>>equ11;
			the_num1>>equ22;
			subtract(name_of_variables,v[equ11-1],v[equ22-1]);
		}
		else if ( command.compare(0,10,"substitute",0,10) == 0)
		{
			string temp2,the_v;
			stringstream the_num2;
			int equ111=0,equ222=0;
			the_num2<<command;
			the_num2>>temp2;
			the_num2>>the_v;
			the_num2>>equ111;
			the_num2>>equ222;
			subtract_for_substitute(name_of_variables,v[equ111-1],v[equ222-1],the_v);
		}
		else if ( command =="D")
		{
			display_the_d_of_var(name_of_variables,v,"not the case");
		}
		else if (command.compare(0,1,"D",0,1) == 0 && command[1]==' ')
		{
			string level1,level2;
			stringstream the_level;
			the_level<<command;
			the_level>>level1;
			the_level>>level2;
			display_the_d_of_var(name_of_variables,v,level2);
		}
		else if ( command=="D_value")
		{
			if (v.size() != name_of_variables.size() )
			{
				cout<<"No solution"<<endl;
			}
			else
			{
				float the_value = get_the_dete(name_of_variables,v,"not the case");
				cout<<the_value<<endl;
			}
		}
		else if ( command=="solve")
		{
			float the_val=get_the_dete(name_of_variables,v,"not the case");
			set<string>::iterator itr1;
			string order;
			float the_val2=0;
			for ( itr1 = name_of_variables.begin(); itr1 != name_of_variables.end() ; itr1++)
			{
				order=*itr1;
				the_val2=get_the_dete(name_of_variables,v,order);
				cout<<order<<"="<<(the_val2/the_val)<<endl;
			}
		}
	

		getline(cin,command);
	}
	
	return 0;
}
// dont forget to clear vector l after each(i) equation and before delete make v[i]=l[i]
// you added & so you call by refrence so hope it wont fuck it up you might delete it
float turn_string_to_flaot( string& s)
{
	return atof(s.c_str());
}

string turn_float_to_srting(float f)
{
	stringstream ss;
	ss<<f;
	return ss.str();

}
// this function returns the string of reapted coffcient and detrimine the start erase index and not do the erase it self from the vector
string find_coffcient_of_repeated( int x, string& the_equation,int& the_start)
{
	string the_coff;
	int index_of_equal = the_equation.find("=");
	// case example x1+2x2=5 the coffceient is 1 of x1
	if ( x-1 == -1)
	{
     the_start = x;
	 the_coff="1";
	}
	// case example x1+x2=5 the coffceient is 1 of x2
	else if ( the_equation[x-1] == '+')
	{
		// check the side 
		if ( x < index_of_equal  )
		{
			the_coff="1";
			the_start= x-1;
		}
		else
		{
			the_coff = "-1";
			the_start = x-1;
		}
	}
	// case example -x1+2x2=5 the coffceient is -1 of x1
	else if ( the_equation[x-1] == '-')
	{
		// check the side 
		the_start= x-1;
		if (  x < index_of_equal  )
		{
			the_coff = "-1";
		}
		else
		{
			the_coff = "1";
		}
	}
	// case example 2x2=x1 the coffceient is -1 of x1
	else if ( the_equation[x-1] == '=' )
	{
		the_start = x;
		the_coff = "-1";
	}
	// case of example genearl case with float and more than on digit coffcients
	else
	{
		for (int i = x-1; i >= 0; i--)
		{
			// keep insert untill it finds a fuckong operator
			if ( the_equation[i] != '+' && the_equation[i] != '-' && the_equation[i] != '=' )
			{
				the_coff.insert(0,1,the_equation[i]);
			}
			
			else if ( the_equation[i] == '+')
			{
				the_start=i;
				if ( x < index_of_equal)
				{
					the_start=i;
					break;
				}
				else
				{
					the_coff.insert(0,"-");
					break;
				}
			}
			else if (the_equation[i] == '-')
			{
				the_start=i;
				if ( x < index_of_equal)
				{
					the_coff.insert(0,"-");
					break;
				}
				else
				{
					break;
				}
			}
			else if ( the_equation[i] == '=' )
			{
				the_coff.insert(0,"-");
				the_start=i+1;
				break;
			}
		}
	}
	return the_coff;
}
/*
// the function that return the cons after taking the eqation
float get_constant(string the_equation)
{
	// the variables which are the start of the cons and the end and the string constants and the float value 
	int index_of_start=0,index_of_end=0;
	string the_constants;
	float the_constants_value=0;

	// for loop to stream over the string
	for (int i = 0; i < the_equation.length(); i++)
	{
		//index of equal 
		int index_of_equal = the_equation.find("=");
		if ( the_equation[i] != '+' && the_equation[i] != '-' && the_equation[i] != '=' && !(isalpha(the_equation[i]) ))
		{ 
			//after finding the start save the index
			index_of_start=i;
			// find the last of the cons and the sign
			for (int k = i; k < the_equation.length(); k++)
			{ 
				// the last or if you are at the end of string remmber to put it up at finding the variable name 
				if (the_equation[k] == '+' || the_equation[k] == '-' || the_equation[k] == '=' || k==(the_equation.length()-1) )
				{
					//end of cons num
					index_of_end=k;
					// make the string of the cons after finding end and last of it
					// the case it is in the last x1+x2=3

					if ( k==the_equation.length()-1)
						the_constants = the_equation.substr(index_of_start,(index_of_end-index_of_start)+1);
					else
					the_constants = the_equation.substr(index_of_start,index_of_end-index_of_start);
					// check the sign
					if ( index_of_start > index_of_equal )
					{
						// before the equal if negative add (-)
						if ( the_equation[i-1] == '-')
						{
							the_constants="-"+the_constants;
							break;
						}
						
					}
					else
					{
						if (the_equation[i-1] == '+' || the_equation[i-1] == '=')
						{
							the_constants ="-"+the_constants;
							break;
						}
					}
					// you break after finding + or - or = or end of string from the loop
					
				}
			}
		}
		else
		{
			// to ignore the rest of the body
			continue;
		}
		// hereeeeeeeeeeeeeeeee after the condition and inside the i loop
		the_constants_value += turn_string_to_flaot(the_constants);
		// erase what you already found and set to zero to start from the begining you started erasing from the digit it self
		the_equation.erase(index_of_start,index_of_end);
		i=0;
	}
	//test line
	cout<<the_constants_value<<endl;
	return the_constants_value;
}
*/
string get_constant(string the_equation)
{
	int index_of_start=0,index_of_end=0;
	string the_constants;
	float the_constants_value=0;

	// for loop to stream over the string
	for (int i = 0; i < the_equation.length(); i++)
	{
		//index of equal 
		int index_of_equal = the_equation.find("=");
		if ( the_equation[i] != '+' && the_equation[i] != '-' && the_equation[i] != '=' && !(isalpha(the_equation[i]) ))
		{ 
			//after finding the start save the index
			index_of_start=i;
			// find the last of the cons and the sign
			for (int k = i; k < the_equation.length(); k++)
			{ 
				// the last or if you are at the end of string remmber to put it up at finding the variable name 
				if (the_equation[k] == '+' || the_equation[k] == '-' || the_equation[k] == '=' || k==the_equation.length()-1 )
				{
					//end of cons num
					index_of_end=k;
					// make the string of the cons after finding end and last of it 
					if ( k==the_equation.length()-1)
					the_constants = the_equation.substr(index_of_start,(index_of_end-index_of_start)+1);
					else
					the_constants = the_equation.substr(index_of_start,index_of_end-index_of_start);
					// check the sign
					if ( index_of_start > index_of_equal )
					{
						// before the equal if negative add (-)
						if ( the_equation[i-1] == '-')
						{
							the_constants="-"+the_constants;
						}
						
					}
					else
					{
						if (the_equation[i-1] == '+' || the_equation[i-1] == '=')
						{
							the_constants ="-"+the_constants;
						}
					}
					// you break after finding + or - or = or end of string from the loop
					break;
				}
			}
		}
		else
		{
			// to ignore the rest of the body
			continue;
		}
		// hereeeeeeeeeeeeeeeee after the condition and inside the i loop
		the_constants_value += turn_string_to_flaot(the_constants);
		// erase what you already found and set to zero to start from the begining you started erasing from the digit it self
		if ( index_of_end==the_equation.length()-1)
		the_equation.erase(index_of_start,(index_of_end-index_of_start)+1);
		else
		the_equation.erase(index_of_start,index_of_end-index_of_start);
		i=0;
	}
	the_constants = turn_float_to_srting(the_constants_value);
	return the_constants;

}
// responsible for returning the equation number
// usless function for now
float print_the_equation(string& s)
{
	string the_num = s.substr(9,3);
	return turn_string_to_flaot(the_num);

}
// function that print the coff of variable
// ask about the call by refrence for the vector 
void print_the_coff(string& s,vector<string> v,int n)
{



	// bug here if the x2 doesnt exist the coffcient is zero


	int index_of_v=0,index_of_c=0;
	string the_variable = s.substr(7,100);
	for (int i = 0; i < n; i++)
	{
		index_of_v =v[i].find(the_variable);
		if( index_of_v != -1)
		cout<<find_coffcient_of_repeated(index_of_v,v[i],index_of_c)<<endl;
		else
			cout<<"0"<<endl;
		
	}

}
// a function that returns bool if the variable is not acatuly reapeated
bool true_or_false(string& s, string& varia , int index_of_re)
{
	int size = varia.length();
	int counter=1;
	for (int i = index_of_re+1; i < s.length(); i++)
	{
		// when it counters a sign
		if ( s[i] == '+' || s[i] == '-' || s[i] == '='  )
		{
			counter=i-index_of_re;
			break;
		}
		// case end of the string
		else if ( i == s.length()-1)
		{
			counter=i-index_of_re+1;
			break;
		}
	}
	// check if the same size 
	if ( counter==size )
	{
		return true;
	}
	else
	{
		return false;
	}
}
// the function that adds the two equations it takes the set of variables and two strings representing the equation
void add(set<string> name_of_variables,string& equ1,string& equ2)
{
	string variable;
	float coff1=0,coff2=0,the_add=0;
	string the_coff,the_add_equation;
	set<string>::iterator itr;
	for ( itr = name_of_variables.begin(); itr != name_of_variables.end(); itr++)
	{
		int no_use=0;
		variable=*itr;
		int index=equ1.find(variable);
		if (index != -1 && true_or_false(equ1,variable,index))
		{
			coff1=turn_string_to_flaot(find_coffcient_of_repeated(index,equ1,no_use));
		}
		else
		{
			coff1=0;
		}
		index = equ2.find(variable);
		if ( index != -1 && true_or_false(equ2,variable,index))
		{
			coff2=turn_string_to_flaot(find_coffcient_of_repeated(index,equ2,no_use));
		}
		else
		{
			coff2=0;
		}
		the_add=coff1+coff2;
		the_coff=turn_float_to_srting(the_add);



		// important bug here if they inhilate each other at first variable
		// x1+x2=6
		//-x1+x3=8



		if ( itr == name_of_variables.begin() && the_add != 0)
		{
			the_add_equation += the_coff+variable;
		}
		else if( the_add != 0)
		{
			if ( the_add > 0)
			{
				the_add_equation += '+'+the_coff+variable;
			}
			else
			{
				the_add_equation += the_coff+variable;
			}
		}
	}
	// add the constant stage
	float cons1=float_constant(equ1);
	float cons2=float_constant(equ2);
	the_add_equation += '='+turn_float_to_srting(cons1+cons2);
	cout<<the_add_equation<<endl;
}
// the same function of add but with minor changes
void subtract(set<string> name_of_variables,string& equ1,string& equ2)
{
	string variable;
	float coff1=0,coff2=0,the_add=0;
	string the_coff,the_add_equation;
	set<string>::iterator itr;
	for ( itr = name_of_variables.begin(); itr != name_of_variables.end(); itr++)
	{
		int no_use=0;
		variable=*itr;
		int index=equ1.find(variable);
		if (index != -1 && true_or_false(equ1,variable,index))
		{
			coff1=turn_string_to_flaot(find_coffcient_of_repeated(index,equ1,no_use));
		}
		else
		{
			coff1=0;
		}
		index = equ2.find(variable);
		if ( index != -1 && true_or_false(equ2,variable,index))
		{
			coff2=turn_string_to_flaot(find_coffcient_of_repeated(index,equ2,no_use));
		}
		else
		{
			coff2=0;
		}
		the_add=coff1-coff2;
		the_coff=turn_float_to_srting(the_add);



		// important bug here if they inhilate each other at first variable
		// x1+x2=6
		//-x1+x3=8



		if ( itr == name_of_variables.begin() && the_add != 0)
		{
			the_add_equation += the_coff+variable;
		}
		else if( the_add != 0)
		{
			if ( the_add > 0)
			{
				the_add_equation += '+'+the_coff+variable;
			}
			else
			{
				the_add_equation += the_coff+variable;
			}
		}
	}
	// add the constant stage
	float cons1=float_constant(equ1);
	float cons2=float_constant(equ2);
	the_add_equation += '='+turn_float_to_srting(cons1-cons2);
	cout<<the_add_equation<<endl;
}

float float_constant(string& equ)
{
	int index1=equ.find('=');
	// be aware from this proplem you made 200 in the substr 


	float cons= turn_string_to_flaot(equ.substr(index1+1,200));
	return cons;

}


// the same function of substract but with just changing the coffs by multiby by the prsentage in second equ
// full of bugs i'm afried



void subtract_for_substitute(set<string> name_of_variables,string& equ1,string& equ2,string& varia)
{
	// the diffrence between substract and susbs 
	
		// important bug x11+x1+x2=3 fixxxxxxxxxxxxxxxxxxxxxx later by functions
	int c1_index=equ1.find(varia);
	int no_use1;
	int c2_index=equ2.find(varia);

	// fix the bug by if condition


	float c1=turn_string_to_flaot(find_coffcient_of_repeated(c1_index,equ1,no_use1));
	float c2=turn_string_to_flaot(find_coffcient_of_repeated(c2_index,equ2,no_use1));

	// the factor to be multblied 
	float the_factor = c1/c2;
	// from here subtract begin 
	string variable;
	float coff1=0,coff2=0,the_add=0;
	string the_coff,the_add_equation;
	set<string>::iterator itr;
	for ( itr = name_of_variables.begin(); itr != name_of_variables.end(); itr++)
	{
		int no_use=0;
		variable=*itr;
		int index=equ1.find(variable);


		// a bug here of the example x11+x1+x2=3 


		if (index != -1 && true_or_false(equ1,variable,index))
		{
			coff1=turn_string_to_flaot(find_coffcient_of_repeated(index,equ1,no_use));
		}
		else
		{

			// don't forget to fix this bug in add and subtract and susbs the bug is x11+x1+x2 it will take x1 first important bug to fix  
			// fixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ittttttttttttttttttttttttttttttttttttttttttttttttttt

			coff1=0;
		}
		index = equ2.find(variable);
		if ( index != -1 && true_or_false(equ2,variable,index))
		{
			coff2=turn_string_to_flaot(find_coffcient_of_repeated(index,equ2,no_use));
		}
		else
		{
			coff2=0;
		}

		//the extra term the_factor

		the_add=coff1-(coff2*the_factor);
		the_coff=turn_float_to_srting(the_add);



		// important bug here if they inhilate each other at first variable
		// x1+x2=6
		//-x1+x3=8



		if ( itr == name_of_variables.begin() && the_add != 0)
		{
			the_add_equation += the_coff+variable;
		}
		else if( the_add != 0)
		{
			if ( the_add > 0)
			{
				the_add_equation += '+'+the_coff+variable;
			}
			else
			{
				the_add_equation += the_coff+variable;
			}
		}
	}
	// add the constant stage
	float cons1=float_constant(equ1);
	float cons2=float_constant(equ2);

	// the extra term the_factor
	the_add_equation += '='+turn_float_to_srting(cons1-(cons2*the_factor));
	cout<<the_add_equation<<endl;
}
void display_the_d(set<string> name_of_variables,vector<string> v)
{
	string variable;
	int no_use=0,index=0;
	float coff=0;
	set<string>::iterator itr;
	for (int i = 0; i < v.size(); i++)
	{
		int count=1;
		for ( itr = name_of_variables.begin(); itr != name_of_variables.end() ; itr++)
		{
			variable=*itr;
			index=v[i].find(variable);
			if (index != -1 )
			{
				if ( count != name_of_variables.size())
				{
				cout<<find_coffcient_of_repeated(index,v[i],no_use)<<"      ";
				}
				else
				{
					cout<<find_coffcient_of_repeated(index,v[i],no_use);
				}
			}
			else
			{
				if ( count != name_of_variables.size())
				{
				cout<<"0"<<"      ";
				}
				else
				{
					cout<<"0";
				}
			}
			
		}
		cout<<endl;
	}
}
// important bug don't forget to fix
void display_the_d_of_var(set<string> name_of_variables,vector<string> v,string vari )
{
	string variable;
	int no_use=0,index=0;
	float coff=0;
	set<string>::iterator itr;
	for (int i = 0; i < v.size(); i++)
	{
		int count=1;
		for ( itr = name_of_variables.begin(); itr != name_of_variables.end() ; itr++)
		{
			variable=*itr;
			index=v[i].find(variable);

			if ( variable==vari)
			{
				
					if (count==1)
					{
						cout<<turn_float_to_srting(float_constant(v[i]))<<"\t";
						count++;
					}
					else
					{
					cout<<turn_float_to_srting(float_constant(v[i]))<<"\t";
					count++;
					}
			
			}
			else if (index != -1 )
			{
				
					if ( count==1)
					{
					cout<<find_coffcient_of_repeated(index,v[i],no_use)<<"\t";
					count++;
					}
					else
					{
					cout<<find_coffcient_of_repeated(index,v[i],no_use)<<"\t";
					count++;
					}
				
			}
			else
			{
				//fix later the zero case 
				if ( count==1)
					{
					cout<<"0"<<"\t";
					count++;
					}
					else
					{
					cout<<"0"<<"\t";
					count++;
					}
			}
			
		}
		cout<<endl;
	}
}
float get_the_dete(set<string> name_of_variables,vector<string> v,string vari )
{
	string variable;
	int no_use=0,index=0;
	float coff=0;
	vector<vector<float> > num;
	float num1[100][100];
	int counter =0;
	set<string>::iterator itr;
	for (int i = 0; i < v.size(); i++)
	{
		vector<float>temp;
		int count=1;
		for ( itr = name_of_variables.begin(); itr != name_of_variables.end() ; itr++)
		{
			variable=*itr;
			index=v[i].find(variable);

			if ( variable==vari)
			{
				
						coff=float_constant(v[i]);
						//temp.push_back(coff);
			num1[i][counter]=coff;
			counter++;
			}
			else if (index != -1 )
			{
				
					
				coff=turn_string_to_flaot(find_coffcient_of_repeated(index,v[i],no_use));
				//temp.push_back(coff);
				num1[i][counter]=coff;
				counter++;
			}
			else
			{
				//fix later the zero case
				coff=0;
				//temp.push_back(coff);
				num1[i][counter]=coff;
				counter++;
			}
			
		}
		//num.push_back(temp);
		counter=0;
	}
	return determinantOfMatrix( num1,v.size());
}

/*
void getCofactor(vector<vector<float> >num , vector<vector<float> > temp, int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
				temp[i][j++] = num[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
 Recursive function for finding determinant of matrix.
   n is current dimension of mat[][]. 
float determinantOfMatrix( vector<vector<float> >num , int n)
{
	
	float D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
		return num[0][0];
 
	vector<vector<float> > temp; // To store cofactors
	
	

	
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
		getCofactor(num, temp, 0, f, n);
		D += sign * num[0][f] * determinantOfMatrix(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}
*/

void getCofactor(float mat[100][100], float temp[100][100], int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of mat[][]. */
float determinantOfMatrix(float mat[100][100], int n)
{
	float D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return mat[0][0];
 
	float temp[100][100]; // To store cofactors
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}

