/* COP3014L -- Debugging Exercise, based on AT&T Network Bug        */
/* See handout associated with this program for more information    */
/* Note: this is not intended to be a good example of coding style. */
/* Last edited: 31/8/2011. */

#include <iostream>
using namespace std;

void make_unitialized(void);
int phone_network(int i, int x, int y);
void init_values_x1(void);
void init_values_part1A(void);
void init_values_part1B(void);
void init_values_part2(void);
void init_default(void);


/* global variables that control phone network */ int val1, val2;

/*--------------------------------------------------------- main */
/* main -- a simple driver function that reads three values,
   which are passed to the function phone_network, which succeeds
   of fails.   Certain combinations of values will call phone_network
   to fail.
*/

int
main (void)
{
  int i, x, y;


  cout << "Enter 3 integers: i, x and y: ";
  

  while ( cin >> i >> x >> y ) {

    /* call this to fake that variables are unitialized */
    make_unitialized();

    if ( phone_network(i, x, y) == 1 )
      cout << "Phone network OK!\n" << endl;
    else
      cout << "Phone network crashes!\n" << endl;

    cout << "Enter 3 integers: i, x and y: ";
  }
  cout << "You didn't enter 3 valid integers -- program exiting." << endl;


  return 0;
}

/*------------------------------------------------------route_that_call */
/*  returns 1 if system intialized OK, 0 if not */ int
route_that_call(void)
{
  if ( val1 >= 0 && val2 >= 0 )
    return 1;
  else
    return 0;
  /* Note: you should never write the above logic as an if statement;
     instead write:
       return ( val1 >= 0 && val2 >= 0 );
     This does the same thing in one line.  See why?
  */

}


/*-------------------------------------------------------phone_network */
/*  phone_network -- initialize global control values, then route call.
 *      This function takes 3 values:  the first, i, is used to select
 *      which initialization function is called.  The 2nd and 3rd
 *      values, x and y, are used to calculate values for the global
 *      control values.  (They're also used  in calculating initial values
 *      for the control values.
 *      After doing the initialization, function route_that_call is
 *      called to do the "real" work of the phone network system.
 */
int
phone_network(int i, int x, int y)
{


  const int i1=1, i2=2, val1=3, val2=5;

  switch (i) {

  case i1:
    init_values_x1();
    break;

  case i2:
    /* for this case, intialization split between several functions */
    if (x == val1) {
      init_values_part1A();

      if (y == val2)
        break;  /* drop out of the if and do init_values_part2() */

      init_values_part1B();
    }

    init_values_part2();
    break;

  default:
    init_default();
  }

  /* call function to make the phone call -- it returns 1 for success */
  return route_that_call();
}


/*-------------------------------------------------------make_unitialized */
/* For this exercise, we'll pretend negative values mean the system 
   is not initialized properly.
*/
void
make_unitialized(void)
{
  val1 = val2 = -999999;
}



/*---------------------------------------------------------init_values_x1 */ void
init_values_x1(void)
{
  val1 = 3;
  val2 = 5;
}

/*-----------------------------------------------------init_values_part1A */ void
init_values_part1A(void)
{
  val1 = 1;
}

/*-------------------------------------------------------init_values_part1B */ void
init_values_part1B(void)
{
  ++val1;
}

/*-------------------------------------------------------init_values_part2 */ void
init_values_part2(void)
{
  val1 = 6;
  val2 = 7;
}

/*-------------------------------------------------------init_default */ void
init_default(void)
{
  val1 = 1;
  val2 = 1;
}



