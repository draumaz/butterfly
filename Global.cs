using System;
using System.IO;
using System.Threading;

namespace Global
{
    public class Friends
    {
        public void Input_Error_Handler()
        {
            Console.WriteLine("\nDid you mean something else?");
            Thread.Sleep(500);
        }
    }
    public class Config
    {
        public string Paths(int m)
        {
            string save_path = "temp.txt";
            string rec_path = "record.txt";
            string save_len = "0\n0\n0\n0\n0\n0\n0\n0\n";
            if (m == 1)
            {
                return save_path;
            }
            if (m == 2)
            {
                return save_len;
            }
            if (m == 3)
            {
                return rec_path;
            }
            return "";
        }
    }
}