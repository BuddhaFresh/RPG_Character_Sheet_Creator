#include "menus.h"
#include "Systems/BRP/BRP.h"
#include "diceroller.h"


//ROADMAP
// 
// 0. txt file version complete
// 0.1 skills
// 0.2 description
// 0.3 page 2
// 1. Move BRP Menus in BRP.cpp
// 2. Load from txt file
// 3. Able to edit a blank sheet (point buy and full custom edit)
// 4. Able to edit randomized sheet
// 5. Make a user defined multi-random character (txt) sheet generater
// 5.1 Make each called random charcter generate a new seed
// 6. basic windows GUI
// 7. exe file installer
// 8. PDF file output
// 8.1 Fillable PDF file output
// 


//Classes
RandomSetUp SEEDER;
Dice ROLL;


int main() 
{//All menus



  
  //Inputs for menus
  int mainMenuInput;
  int optionsMenuInput;
  int diceMenuInput;
  int newMenuInput;
  int charKeepInput;

  //Generate a new seed at boot
  SEEDER.randomSeed();

  //Makes a new folder in Characters for any added Systems
  FolderOriginBRP();
  
  while(true) 
  {//MAIN MENU
    std::cout << "\n\n<>~~~~~~~~~~<>~~~~~~~~~~<>~~~~~~~~~~<>\n";
    std::cout << "Welcome to Character Sheet Creator\n\t\t\tMain Menu\n";
    std::cout << "1. New Sheet\n";
    std::cout << "2. Load Sheet\n";
    std::cout << "3. Dice Roller\n";
    std::cout << "4. Options\n";
    std::cout << "\n0. Exit\n";
    std::cout << "<>~~~~~~~~~~<>~~~~~~~~~~<>~~~~~~~~~~<>\n\n";

    std::cout << "Please Enter Your Command\n";
    std::cin >> mainMenuInput;

      switch (mainMenuInput)
      {//Main menu input start    
        case 1: //New Sheet
          while(true)
          {//New Sheet menu 
            std::cout << "\n\n<>----------<>----------<>----------<>\n";
            std::cout << "\t\t\tNew Sheet Menu\n";
            std::cout << "New Sheet not availible\n\n";
            std::cout << "1. DOJO [Make 5 random BRP chars]\n\n";
            std::cout << "2. DOJO [3d6]\n\n";
            std::cout << "3. DOJO [make random BRP char rolls]\n";
            std::cout << "\n0. Return to Main Menu\n";
            std::cout << "<>----------<>----------<>----------<>\n\n";
  
            std::cout << "Please Enter Your Command\n";
            std::cin >> newMenuInput;
            
            switch(newMenuInput)
            {//New Sheet menu input start
              case 1://temp for testing
                for (int i = 0; i < 5; i++)
                {
                 BRP_human_base BRPChar0(ThreeDSix(),ThreeDSix(),ThreeDSix(),ThreeDSix(),ThreeDSix(),TwoDSixPlusSix(),TwoDSixPlusSix());
                BRPChar0.fullrandom(SEEDER); 
                }
                break;
              case 2://temp for testing
                for (int i = 0; i < 20; i++)
                {
                 std::cout << ThreeDSix() << std::endl; 
                }
                break;
              case 3://temp for testing
                {//case 3
                  BRP_human_base BRPChar0(ThreeDSix(),ThreeDSix(),ThreeDSix(),ThreeDSix(),ThreeDSix(),TwoDSixPlusSix(),TwoDSixPlusSix());
                  BRPChar0.PlayerName();
                  BRPChar0.fullrandom(SEEDER);
                  
                  while(true)
                  {//save character menu
                    std::cout << "\n\n<>##########<>##########<>##########<>\n";
                    std::cout << "\t\tSave this charcater?" << std::endl;
                    std::cout << "1. Save as txt file" << std::endl;
                    std::cout << "\n0. Return" << std::endl;
                    std::cout << "<>##########<>##########<>##########<>\n\n";
                    std::cin >> charKeepInput;
                    
                    switch(charKeepInput)
                    {//save character input
                      case 1:
                        BRPChar0.CharName();
                        BRPChar0.printChar(SEEDER);
                        break;
                      case 0:
                        break;
                      default:
                        std::cout << "\nNot one of the options";
                        break;
                    }//save character input end
                    
                    if (charKeepInput == 0 || charKeepInput == 1) break;
                    
                  }//save character menu end
                  
                break;
                  
                }//case 3 end
              default:
                std::cout << "Please enter one of the listed options";
                break;
            }//New Sheet menu input end
            if (newMenuInput == 0) break;
          }//New Sheet menu end
          break;
          
        case 2: //Load Sheet
          std::cout << "\nLoad Sheet not availible\n\n";
          break;
        
        case 3: //Dice Roller
          while (true)
            {//Dice Roller menu
              std::cout << "\n\n<>++++++++++<>++++++++++<>++++++++++<>\n";
              std::cout << "\t\t\tDice Choices\n";
              std::cout << "1. Roll a D4\n";
              std::cout << "2. Roll a D6\n";
              std::cout << "3. Roll a D8\n";
              std::cout << "4. Roll a D10\n";
              std::cout << "5. Roll a D12\n";
              std::cout << "6. Roll a D20\n";
              std::cout << "7. Roll a D100\n";
              std::cout << "\n0. Return to Options\n";
              std::cout << "<>++++++++++<>++++++++++<>++++++++++<>\n\n";
      
              std::cout << "Please make your selection\n";
              std::cin >> diceMenuInput;
  
              switch (diceMenuInput)
              {//Dice Roller input
                case 1:
                  std::cout << "\nYou rolled a four-sided die and got a " << ROLL.Dfour() << std::endl;
                  break;
                case 2:
                  std::cout << "\nYou rolled a six-sided die and got a " << ROLL.Dsix() << std::endl;
                  break;
                case 3:
                  std::cout << "\nYou rolled an eight-sided die and got a " << ROLL.Deight() << std::endl;
                  break;
                case 4:
                  std::cout << "\nYou rolled a ten-sided die and got a " << ROLL.Dten() << std::endl;
                  break;
                case 5:
                  std::cout << "\nYou rolled a twelve-sided die and got a " << ROLL.Dtwelve() << std::endl;
                  break;
                case 6:
                  std::cout << "\nYou rolled a twenty-sided die and got a " << ROLL.Dtwenty() << std::endl;
                  break;
                case 7:
                  std::cout << "\nYou rolled a hundred-sided die and got a " << ROLL.Donehundred() << std::endl;
                  break;
                case 0:
                  break;
                default:
                 std::cout << "Please enter one of the listed options";
                 break;
              }//Dice Roller input end
              if (diceMenuInput == 0) break;
            }//Dice Roller menu end
            break;
        
        case 4: //Options
        while (true)  
        {//Options sub-menu start
          std::cout << "\n\n<>==========<>==========<>==========<>\n";
            std::cout << "\t\t\t\tOptions\n";
            std::cout << "1. Input Manual Seed \n(Current Seed: "<< SEEDER.currentSeed <<")\n";
            std::cout << "2. Generate New Seed\n";
            std::cout << "\n0. Return to Main Menu\n";
            std::cout << "<>==========<>==========<>==========<>\n\n";
  
            std::cout << "Please Enter Your Command\n";
            std::cin >> optionsMenuInput;
          
            switch (optionsMenuInput)
              {//Options input
                case 1:
                  SEEDER.userSeed();
                  break;
                case 2:
                  std::cout << "\nNew Seed has been generated\n";
                  SEEDER.randomSeed();
                  break;
                case 0:
                  std::cout << "\nReturning to Main Menu\n";
                  break;
                default: 
                  std::cout << "\nNot an availible command\n";
                  break;
              }//Options input end
          if (optionsMenuInput == 0) break; 
        }//Options sub-menu end
        break;
        case 0: //Exit
          std::cout << "\nExiting Program\nGood Bye!\n";
          return 0;
        default: 
          std::cout << "\nNot an availible command\n";
          break;
      }//Main menu input end
  }//MAIN MENU end
}//All menus end