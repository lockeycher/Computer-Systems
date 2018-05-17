/*-------------------------------------------------------------------------*
 *---									---*
 *---		celebrityChefs.cpp					---*
 *---									---*
 *---	    This file defines classes, methods and functions that	---*
 *---	*ought* to implement N celebrity chefs who prepare meals for	---*
 *---	M notable gourmands.  All share a single Table object, on which	---*
 *---	at most one Dish instance may exist at a time.			---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		Joseph Phillips		2018 May 4	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//--									--//
//	Compile with: 							  //
//	$ g++ celebrityChefs.cpp -o celebrityChefs -g -lpthread		  //
//--									--//


//--									--//
//			Common include file sequence:			  //
//--									--//

#include	<cstdlib>
#include	<cstdio>
#include	<string>
#include	<iostream>
#include	<unistd.h>
#include	<pthread.h>



//--									--//
//				Common constants:			  //
//--									--//

//  PURPOSE:  To tell how many Dish instances thta each Chef instance prepares,
//	and that each Gourmand instance consumes.
const int	NUM_DISHES_TO_DO		= 32;

//  PURPOSE:  To tell the maximum number of seconds that it takes either to
//	prepare or consume a dish.
const int	MAX_SLEEP_SECONDS	= 3;



//--									--//
//		Dish-related constants, classes and functions:		  //
//--									--//

//  PURPOSE:  To define a type telling if modifying phrase should come before
//	or after the noun phrase it modifies.
typedef	enum	{
		  BEFORE_MODLOC,
		  AFTER_MODLOC
		}
		modifierLocation_t;

//  PURPOSE:  To hold information on a clause that grammatically modifies a
//	Dish instance.
class	DishModifier
{
  //  I.  Member vars:
  //  PURPOSE:  To point to the modifying phrase.
  const char*		modifierCPtr_;

  //  PURPOSE:  To tell if modifying phrase should come before or after the
  //	noun phrase it modifies.
  modifierLocation_t	modifierLoc_;

  //  II.  Disallowed auto-generated methods:
  //  No copy-assignment op:
  DishModifier		operator=
			(const DishModifier&
			);
protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to represent that the modifying phrase
  //	pointed to by 'newCPtr' should come before or after the noun phrase
  //	that it modifies according to 'newModifierLoc'.  No return value.
  DishModifier	(const char*		newCPtr,
		 modifierLocation_t	newModifierLoc
		) :
		modifierCPtr_(newCPtr),
		modifierLoc_(newModifierLoc)
		{ }

  //  PURPOSE:  To make '*this' a copy of 'source'.  No parameters.  No
  //	return value.
  DishModifier	(const DishModifier&	source
		) :
		modifierCPtr_(source.modifierCPtr_),
		modifierLoc_(source.modifierLoc_)
		{ }

  //  V.  Accessors:
  //  PURPOSE:  To return a pointer to the modifying phrase.  No parameters.
  const char*	getModifierCPtr	()
				const
				throw()
				{ return(modifierCPtr_); }

  //  PURPOSE:  To return a 'modifierLocation_t' value telling if modifying
  //	phrase should come before or after the noun phrase it modifies.
  modifierLocation_t
		getModifierLoc	()
				const
				throw()
				{ return(modifierLoc_); }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc. work of class:

};



//  PURPOSE:  To list dish modifiers.
const DishModifier
		DISH_MODIFIER_ARRAY[]
		= { DishModifier("triple deep-fried",BEFORE_MODLOC),
		    DishModifier("sauteed in liposuctioned human belly fat",
		    		 AFTER_MODLOC
				),
		    DishModifier("crawling with cockroaches",AFTER_MODLOC),
		    DishModifier("drenched in 18 molar "
		    		    "*food-grade* sulfuric acid",
		    		 AFTER_MODLOC
				),
		    DishModifier("tape worm infested",BEFORE_MODLOC),
		    DishModifier("infused with mad-cow prions",AFTER_MODLOC),
		    DishModifier("glowing with Cobalt-60, Strontium-90 and"
					" Radium-226 radionuclidic goodness",
		    		 AFTER_MODLOC
				),
		    DishModifier("with a side of ground glass",AFTER_MODLOC)
		  };

const int	NUM_MODIFIERS	= ( sizeof(DISH_MODIFIER_ARRAY)
      				    / sizeof(DishModifier)
				  );


//  PURPOSE:  To list dish nouns.
const char*	NOUN_NAME_ARRAY[]
		= {"earthworms",
		   "grass",
		   "potassium cyanide solution",
		   "crickets",
		   "american cheese",
		   "dirt",
		   "formaldehyde",
		   "monosodium glutamate",
		   "eye of newt, and toe of frog; wool of bat, and tongue of dog",
		   "Salmonella stew",
		   "banana slugs",
		   "high-fructose corn syrup",
		   "trans-fat",
		   "botulism beef broth"
		  };

const int	NUM_NOUNS	= ( sizeof(NOUN_NAME_ARRAY)
      				    / sizeof(const char*)
				  );

//  PURPOSE:  To represent a dish.
class		Dish
{
  //  I.  Member vars:
  //  PURPOSE:  To tell the modifier that describes '*this' Dish instance.
  int		modifierIndex_;

  //  PURPOSE:  To tell the noun that describes '*this' Dish instance.
  int		nounIndex_;

  //  II.  Disallowed auto generated methods:
  //  No copy assignment op:
  Dish&		operator=
		(const Dish&	source
  		);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructors, assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To randomly create a dish.  No parameters.  No return value.
  Dish		()
  {
    modifierIndex_	= rand() % NUM_MODIFIERS;
    nounIndex_		= rand() % NUM_NOUNS;
  }

  //  PURPOSE:  To make '*this' Dish a copy of 'source'.  No return value.
  Dish		(const Dish&	source
  		) :
		modifierIndex_(source.modifierIndex_),
		nounIndex_(source.nounIndex_)
  {
  }

  //  PURPOSE:  To release resources.  No parameters.  No return value.
  ~Dish		()
  {
    std::cout << toString() << " eaten to the last crumb or drop!\n";
  }

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return a 'string' representation of '*this'.  No parameters.
  std::string	toString	()
  				const
  {
    std::string	toReturn;

    if  (DISH_MODIFIER_ARRAY[modifierIndex_].getModifierLoc() == BEFORE_MODLOC)
    {
      toReturn	 = DISH_MODIFIER_ARRAY[modifierIndex_].getModifierCPtr();
      toReturn	+= " ";
      toReturn	+= NOUN_NAME_ARRAY[nounIndex_];
    }
    else
    {
      toReturn	 = NOUN_NAME_ARRAY[nounIndex_];
      toReturn	+= " ";
      toReturn	+= DISH_MODIFIER_ARRAY[modifierIndex_].getModifierCPtr();
    }

    return(toReturn);
  }

};


//  PURPOSE:  To write 'dish' to 'os'.  Returns reference to 'os'.
std::ostream&	operator<<	(std::ostream&	os,
				 const Dish&	dish
				)
{
  //  I.  Application validity check:

  //  II.  Output:
  os << dish.toString();

  //  III.  Finised:
  return(os);
}


//--									--//
//		Chef-related constants, classes and functions:		  //
//--									--//

class		Chef;

//  PURPOSE:  To tell possible names of Chef instances.
const char*	CHEF_NAME_ARRAY[]
		= {"Gordon \"Hittite-smiter\" Ramesses II",
		   "Mrs Nellie Lovett"
		  };

const int	NUM_CHEFS	= ( sizeof(CHEF_NAME_ARRAY)
      				    / sizeof(const char*)
				  );


//  PURPOSE:  To write 'chef' to 'os'.  Returns reference to 'os'.
std::ostream&	operator<<	(std::ostream&	os,
				 const Chef&	chef
				);


//  PURPOSE:  To represent a Chef.
class		Chef
{
  //  I.  Member vars:
  //  PURPOSE:  To tell identity of '*this' Chef.
  int		index_;

  //  II.  Disallowed auto-generated methods:
  //  No copy assignment op:
  Chef&		operator=
		(const Chef&	source
  		);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructors, assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Chef to have identity 'newIndex'.
  //	No return value.
  Chef		(int	newIndex
  		) :
		index_(newIndex)
		{
		}

  //  PURPOSE:  To make '*this' Chef a copy of 'source'.  No return value.
  Chef		(const Chef&	source
		) :
		index_(source.index_)
		{
		}

  //  PURPOSE:  To release resources.  No parameters.  No return value.
  ~Chef		()
  		{
		  std::cout << toString()
			    << " cleans the pots and goes home.\n";
		}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc. work of class:
  //  PURPOSE:  To return a pointer to newly created 'Dish' instance.
  //	No parameters.
  Dish*		prepare		()
  		{
		  Dish*	toReturn	= new Dish();

		  std::cout
			<< *this
			<< ": \"My latest creation!  "
			<< *toReturn
			<< "!\"\n";
		 return(toReturn);
		}

  //  PURPOSE:  To return a 'string' representation of '*this'.  No parameters.
  std::string	toString	()
  				const
		{
		  return(CHEF_NAME_ARRAY[index_]);
		}

};


//  PURPOSE:  To write 'chef' to 'os'.  Returns reference to 'os'.
std::ostream&	operator<<	(std::ostream&	os,
				 const Chef&	chef
				)
{
  //  I.  Application validity check:

  //  II.  Output:
  os << chef.toString();

  //  III.  Finised:
  return(os);
}



//--									--//
//		Gourmand-related constants, classes and functions:	  //
//--									--//

class		Gourmand;


//  PURPOSE:  To tell possible names of Gourmand instances.
const char*	GOURMAND_NAME_ARRAY[]
		= {"Wimpy",	// "J. Wellington Wimpy",
		   "Jughead"	// "Forsythe Pendleton \"Jughead\" Jones III"
		  };

const int	NUM_GOURMANDS	= ( sizeof(GOURMAND_NAME_ARRAY)
      				    / sizeof(const char*)
				  );

//  PURPOSE:  To tell possible Gourmand responses to Dish instances.
const char*	GOURMAND_RESPONSE_ARRAY[]
		= { " \"My compliments to the chef!\"\n",
		    " \"Them's good eatins'!\"\n",
		    " \"May I have another to-go?\"\n",
		    " \"It just needs a *dash* of salt.\"\n",
		    " \"I'll gladly pay you Thursday"
			" for a hamburger today!\"\n",
		    " \"No special sauce?!?!\"\n",
		    " \"The outside's too hot,"
			" the inside's too cold,"
			" the middle's JUST right!\"\n",
		    " \"YUCK!  I'm reporting you"
			" to the Board of Health!\"\n"
		  };

const int	  NUM_GOURMAND_RESPONSES
		  = ( sizeof(GOURMAND_RESPONSE_ARRAY) / sizeof(const char*) );


//  PURPOSE:  To write 'gourmand' to 'os'.  Returns reference to 'os'.
std::ostream&	operator<<	(std::ostream&	os,
				 const Gourmand&	gourmand
				);


//  PURPOSE:  To represent a Gourmand.
class		Gourmand
{
  //  I.  Member vars:
  //  PURPOSE:  To tell identity of '*this' Gourmand.
  int		index_;

  //  II.  Disallowed auto-generated methods:
  //  No copy assignment op:
  Gourmand&	operator=
		(const Gourmand&	source
  		);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructors, assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Gourmand to have identity 'newIndex'.
  //	No return value.
  Gourmand	(int	newIndex
  		) :
		index_(newIndex)
  		{
		}

  //  PURPOSE:  To make '*this' Gourmand a copy of 'source'.  No return value.
  Gourmand	(const Gourmand&	source
		) :
		index_(source.index_)
		{
		}

  //  PURPOSE:  To release resources.  No parameters.  No return value.
  ~Gourmand	()
  		{
		  std::cout << toString()
			    << " belches loudly and sleeps soundly.\n";
		}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc. work of class:
  //  PURPOSE:  To eat (and thus destroy) '*dishPtr'.  No return value.
  void		consume		(Dish*	dishPtr
  				)
  		{
		  std::cout << *this
		  	    << GOURMAND_RESPONSE_ARRAY
					[rand() % NUM_GOURMAND_RESPONSES];
		  delete(dishPtr);
		}

  //  PURPOSE:  To return a 'string' representation of '*this'.  No parameters.
  std::string	toString	()
  				const
		{
		  return(GOURMAND_NAME_ARRAY[index_]);
		}


};


//  PURPOSE:  To write 'gourmand' to 'os'.  Returns reference to 'os'.
std::ostream&	operator<<	(std::ostream&	os,
				 const Gourmand&	gourmand
				)
{
  //  I.  Application validity check:

  //  II.  Output:
  os << gourmand.toString();

  //  III.  Finised:
  return(os);
}



//--									--//
//		Table-related constants, classes and functions:	  //
//--									--//

class		Table
{
  //  I.  Member vars:
  //  PURPOSE:  To point to the single dish that is currently on '*this' Table
  //	(if there is one).
  Dish*			dishPtr_;

  //  PURPOSE:  To implement mutual exclusion.
  //  PERHAPS ADD SOME VARS HERE
  pthread_mutex_t	lock_;
  pthread_cond_t	notEmpty_;
  pthread_cond_t	notFull_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  Table		(const Table&	source
		);

  //  No copy assignment op:
  Table&	operator=
		(const Table&	source
  		);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructors, assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Table to initially have no dishes.  No
  //	parameters.  No return value.
  Table		() :
  		dishPtr_(NULL)
		{
		  //  PERHAPS INITIALIZE SOME VARS HERE
          pthread_mutex_init(&lock_,NULL);
          pthread_cond_init(&notEmpty_,NULL);
          pthread_cond_init(&notFull_,NULL);
		}

  //  PURPOSE:  To release resources.  No parameters.  No return value.
  ~Table	()
  		{
		  //  PERHAPS DESTROY SOME VARS HERE
          pthread_mutex_destroy(&lock_);
          pthread_cond_destroy(&notEmpty_);
          pthread_cond_destroy(&notFull_);
		}

  //  V.  Accessors:
  //  PURPOSE:  To return 'dishPtr
  Dish*		getDishPtr	()
  				const
		{
		  return(dishPtr_);
		}


  //  VI.  Mutators:

  //  VII.  Methods that do main and misc. work of class:
  //  PURPOSE:  To have 'chef' attempt to place '*newDishPtr' on '*this' Table
  //	(that is, set 'dishPtr_' to 'newDishPtr').  This cannot be done if
  //	there already is a Dish present (that is, if 'dishPtr_ != NULL').  If
  //	there is a Dish present then the Chef should complain vociferously
  //	and wait until the old Dish is cleared.  No return value.
  void		serve		(Chef&		chef,
				 Dish*		newDishPtr
  				)
  		{
		  //  MAKE THIS THREAD-SAFE, PLEASE
          pthread_mutex_lock(&lock_);

          while (dishPtr_ != NULL)
          {
	      printf("WOULD YOU CLEAR THAT EFF-ING DISH OFF THE TABLE!\n");
              pthread_cond_wait(&notFull_,&lock_);
          }

		  dishPtr_	= newDishPtr;
		  sleep( (rand() % MAX_SLEEP_SECONDS) + 1);
		  std::cout
			<< chef
			<< ": \""
			<< *getDishPtr()
			<< " is served!\"\n";
          pthread_cond_signal(&notEmpty_);
          pthread_mutex_unlock(&lock_);
		}

  //  PURPOSE:  To have 'gourmand' attempt to remove 'dishPtr_' from '*this'
  //	Table (that is, return the old value of 'dishPtr_' and set it to
  //	'NULL').  This cannot be done if there is no Dish present (that is, if
  //	'dishPtr_ == NULL').  If there is no Dish present then the Gourmand
  //	should complain vociferously and wait until a Dish is served.  Returns
  //	the old value of 'dishPtr_' and sets 'dishPtr_' to 'NULL'.
  Dish*		eatFrom		(Gourmand&		gourmand
  				)
		{
		  //  MAKE THIS THREAD-SAFE, PLEASE
          pthread_mutex_lock(&lock_);

          while (dishPtr_ == NULL)
          {
	      printf("Feed me, Seymour!\n");
              pthread_cond_wait(&notEmpty_,&lock_);
          }

		  Dish*	toReturn	= getDishPtr();
		  std::cout
			<< gourmand
			<< ": \"That "
			<< *getDishPtr()
			<< " looks yummy!\"\n";
		  sleep( (rand() % MAX_SLEEP_SECONDS) + 1);
		  dishPtr_  = NULL;
          pthread_cond_signal(&notFull_);
          pthread_mutex_unlock(&lock_);
		  return(toReturn);
		}
};


//  PURPOSE:  To serve as the global singleton Table instance.
Table		table;


//  PURPOSE:  To have the Chef pointed to by 'void*' ptr 'vPtr' execute
//	its 'prepare()' method 'NUM_DISHES_TO_DO' times and 'serve()' the
//	resulting Dish instances on 'table' 'NUM_DISHES_TO_DO' times.
void*		cook	(void*		vPtr
			)
{
  Chef*	chefPtr	= (Chef*)vPtr;

  //  PERHAPS A LOOP HERE
  for (int i = 0; i < NUM_DISHES_TO_DO; i++)
  {
      Dish* dish = chefPtr -> prepare();
      table.serve(*chefPtr, dish);
  }

  delete (chefPtr);

  return(NULL /* CHANGE IF YOU WANT */);
}


//  PURPOSE:  To have the Gourmand pointed to by 'void*' ptr 'vPtr' execute
//	its 'eatFrom()' method 'NUM_DISHES_TO_DO' times on 'table' and to
//	'consume()' the resulting Dish instances 'NUM_DISHES_TO_DO' times.
void*		eat	(void*		vPtr
			)
{
  Gourmand*	gourmandPtr	= (Gourmand*)vPtr;

  //  PERHAPS A LOOP HERE
  for (int i = 0; i < NUM_DISHES_TO_DO; i++)
  {
      Dish* dish = table.eatFrom(*gourmandPtr); // use "."" for objects and "->" for ptr
      gourmandPtr -> consume(dish);
  }

  delete(gourmandPtr);

  return(NULL /* CHANGE IF YOU WANT */);
}


//  PURPOSE:  To harass CSC 407 students into learning thread programming
//	and thread-safe producer-consumer buffer creation.  If 'argc >= 2' then
//	'argv[1]' is used as a random number seed.  Return 'EXIT_SUCCESS' to
//	OS.
int		main	(int		argc,
			 char*		argv[]
			)
{
  //  I.  Application validity check:

  //  II.  Let's eat!
  //  II.A.  Initialize random number generator:
  if  (argc >= 2)
    srand(atoi(argv[1]));

  //  II.B.  Create Chef and Gourmand threads:
  pthread_t	chefIds[NUM_CHEFS];
  pthread_t	gourmandIds[NUM_CHEFS];

  //  PERHAPS A LOOP HERE
  for (int i = 0; i < NUM_CHEFS; i++)
  { 
      Chef*	newChef	= new Chef(i);
      pthread_create(&chefIds[i], NULL, cook, newChef);
  }

  for (int i = 0; i < NUM_GOURMANDS; i++)
  { 
      Gourmand*	newGourmand	= new Gourmand(i);
      pthread_create(&gourmandIds[i], NULL, eat, newGourmand);
  }

  //  II.C.  Wait for Chef and Gourmand threads:
  //  PERHAPS A LOOP HERE
   for(int i = 0; i < NUM_CHEFS; i++){
    pthread_join(chefIds[i], NULL);
  }

  for(int i = 0; i < NUM_GOURMANDS; i++){
    pthread_join(gourmandIds[i], NULL);
  }

  //  III.  Finished:
  return(EXIT_SUCCESS);
}
