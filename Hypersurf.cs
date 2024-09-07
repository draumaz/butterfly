using System;
using InGame;
using Game_Data;

namespace Hypersurf
{
    internal class Surfer
    {
        public void Hopper()
        {
            Console.Clear();
            var IO = new File_Processing.IO();
            var BA = new InGame.InBattle();
            IO.Exists_Temp();
            IO.Exists_Record();
            BA.Battle_Header();
            BA.Battle_Options();
            Hopper();
        }
        public void False_Hopper(string Action_Num)
        {
            Console.Clear();
            var BA = new InGame.InBattle();
            var FK = new Game_Data.Fake_Surf();
            BA.Battle_Header();
            Console.WriteLine("\nFIGHT [1]\nITEMS [2]\nSPARE [3]\n");
            FK.Surf_One(Action_Num);
        }
    }
}
