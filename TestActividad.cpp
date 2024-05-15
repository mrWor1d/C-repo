#include <iostream>
#define PRINTLINE() cout <<'\n'<<"------------------------------------------------------------" <<'\n'<< endl;
using namespace std;

//class to answer the first question
void firstQuestion()
{
    //delcare and initialize an integer variable
    int myInt = 3;

    //creating a pointer referencing the variable above
    int *ptr = &myInt;

    //print the value of the variable by referencing the pointer    
    cout << "The value of myInt is: " << myInt <<endl;
    cout << "Showing the value of myInt using the pointer: " << *ptr <<'\n'<< endl;

    //print the address of the variable
    cout << "The address of myInt is: " << &myInt << endl;
    cout << "Showing the address of myInt using the pointer: " << ptr <<'\n'<< endl;

    //print the address of the pointer
    cout << "The address of the pointer is: " << &ptr <<'\n'<< endl;

}// end of FirstQuestion



//class to answer the second question
void secondQuestion() 
{
    //declare and initialize an integer variable
    int myInts[]= {1, 2, 3, 4, 5};

    //creating a pointer referencing the variable above
    int *ptr = &myInts[0];

    //variable to store the size of the array
    int length = sizeof(myInts)/sizeof(myInts[0]);

    //print the value of all the elements of the array by referencing the pointer
    for (int i = 0; i < length; i++) {
        cout << "The value of myInts[" << i << "] is: " << myInts[i] << endl;
        cout << "Showing the value of myInts[" << i << "] using the pointer: " << (*ptr+i)<<'\n' << endl;
    }

    //print the address of all the elements of the array by referencing the pointer
    for (int i = 0; i < length; i++) {
        cout << "The address of myInts[" << i << "] is: " << &myInts[i] << endl;
        cout << "Showing the address of myInts[" << i << "] using the pointer: " << (ptr+i)<<'\n'<< endl;
    }

}// end of SecondQuestion



//class to answer the third question
void thirdQuestion()
{
    //declare and initialize two integer variables
    int myInt1 = 3,
        myInt2 = 9;

    //exchange the values of the variables using pointers
    int *ptr1 = &myInt1,
        *ptr2 = &myInt2;

    //print the initial values
    cout << "Before swapping: "<< "myInt1 = " << myInt1 << ", myInt2 = " << myInt2 <<'\n'<< endl;

    //swap the values using pointers
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;

    //print the swapped values
    cout << "After swapping: " <<"myInt1 = " << myInt1<<", myInt2 = " << myInt2 <<'\n'<< endl;
    
}// end of ThirdQuestion


//class to answer the fourth question
class Estudiante
{
    private:
        //declare the attributes of the class
        string nombre_,
               apellido_;
        int edad_;

    public:
        //declare the methods of the class

        //setters
        Estudiante& setNombre (string nombre) { this->nombre_ = nombre; return *this; }
        Estudiante& setApellido (string apellido) { this->apellido_ = apellido; return *this; }
        Estudiante& setEdad (int edad) { this->edad_ = edad; return *this; }

        //getters
        const string getNombre () const { return this->nombre_; }
        const string getApellido () const { return this->apellido_; }
        const int getEdad () const { return this->edad_; }

        //declare the constructor of the class
        Estudiante (string nombre, string apellido, int edad)
        {
            this->nombre_ = nombre;
            this->apellido_ = apellido;
            this->edad_ = edad;            
        }

        //declare the destructor of the class
        ~Estudiante () { cout << "The student " << nombre_ << " has been deleted" << endl; }

};// end of Estudiante


int main ()
{
    cout<< "--------------Start of the activity--------------" << endl;
    PRINTLINE();

    //call the class to answer the first question
    firstQuestion();
    PRINTLINE();

    //call the class to answer the second question
    secondQuestion();
    PRINTLINE();

    //call the class to answer the third question
    thirdQuestion();
    PRINTLINE();

    //call the class to answer the fourth question
    Estudiante *estudiante = new Estudiante("Juan", "Perez", 20);

    //print the attributes of the object
    cout << "The student's name is: " << estudiante->getNombre() << endl;
    cout << "The student's last name is: " << estudiante->getApellido() << endl;
    cout << "The student's age is: " << estudiante->getEdad() << endl;
    
    //set new values to the attributes of the object
    estudiante->setNombre("Maria").setApellido("Gomez").setEdad(25); 
    PRINTLINE();

    //print the new attributes of the object
    cout << "The student's new name is: " << estudiante->getNombre() << endl;
    cout << "The student's new last name is: " << estudiante->getApellido() << endl;
    cout << "The student's new age is: " << estudiante->getEdad() << endl;
    PRINTLINE();

    cout<< "--------------End of the activity--------------" << endl;

    delete estudiante;

    return 0;

}// end of main