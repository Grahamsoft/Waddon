/******************************************************************************
* Filename		:	Form1.cs
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	Basic Scheduling Server to Set and Depart a Block Controller.
*					Contains a thread 't' to read and send Comms.
*********************************************************************************/
// THIS VERSION IS A PROTOTYPE AND HAS NO CODING STANDARD.
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO.Ports;

namespace Scheduling_Server
{
    public partial class Form1 : Form
    {    
        static SerialPort SP;   
        static string send = "";
        private Thread t;
        
        public Form1()
        {
            t = new Thread(Comms);
            t.Start();
            InitializeComponent();
        }
        static void Comms()
        {
            string NullChar = "\0";
            string read = "";
            string readchar= "|";
            string readstring = "";
            SP = new SerialPort();
            SP.PortName = "COM1";
            SP.BaudRate = 9600;
            SP.DataBits = 8;
            SP.StopBits = StopBits.One;
            SP.Parity = Parity.None;
            SP.ReadTimeout = 8000;
            SP.WriteTimeout = 8000;

                SP.Open();
                while (true)
                {
                    if (SP.BytesToRead > 0)
                    {
                        try
                        {
                            readchar = ((char)SP.ReadChar()).ToString();
                            if (readchar == NullChar)
                            {
                               // SP.Write( readstring );
                               // SP.Write( NullChar );

                                while ( readstring[0] != '<' )
                                {
                                    readstring.Remove(0, 1);
                                }
                                if (readstring != "<debug>nomsg</debug>")
                                {
                                    readstring = readstring + NullChar;
                                    SP.Write(readstring);
                                }
                                else
                                {
                                    MessageBox.Show("Comms tested sucessfully.");
                                }
                                readstring = "";
                            }
                            else
                            {
                                readstring = readstring + readchar;
                            }
                        }
                        catch
                        {
                        }
                    }    
                    if (send != "")
                    {
                        send = send + NullChar;
                        SP.Write( send );
                        send = "";
                    }
                    Thread.Sleep(500);
                }       
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ResetAll();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string tosend = "";;
            tosend = "<to>";
            if ( ToLondon.Checked == true )
            {
                tosend += "002";
            }
            else if ( ToWeymouth.Checked == true )
            {
                tosend += "001";
            }
            tosend += "</to>";
            tosend += "<from>000</from>";

            if (ActionDepart.Checked == true)
            {
                tosend += "<action>depart</action>";
            }
            else if (ActionSet.Checked == true)
            {
                tosend += "<action>set</action>";
            }

            if (OrgPlat1.Checked == true)
            {
                tosend += "<originplatform>1</originplatform>";
            }
            else if (OrgPlat2.Checked == true)
            {
                tosend += "<originplatform>2</originplatform>";
            }

            if (DesLon.Checked == true)
            {
                tosend += "<destination>wat</destination>";
            }
            else if (DesWey.Checked == true)
            {
                tosend += "<destination>wey</destination>";
            }

            if (DesPlat1.Checked == true)
            {
                tosend += "<platform>1</platform>";
            }
            else if (DesPlat2.Checked == true)
            {
                tosend += "<platform>2</platform>";
            }

            if (TTbr47c1.Checked == true)
            {
                tosend += "<traintype>br47c1</traintype>";
            }
            else if (TTemu2.Checked == true)
            {
                tosend += "<traintype>emu2</traintype>";
            }

            textBox1.Text = tosend;
            send = tosend;
            ResetAll();
        }

        private void ToWeymouth_CheckedChanged(object sender, EventArgs e)
        {

            if ( ( ToWeymouth.Checked == true ) || ( ToLondon.Checked == true ) )
            {
                ActionDepart.Enabled    = true;
                ActionSet.Enabled       = true;
            }
        }

        private void ToLondon_CheckedChanged(object sender, EventArgs e)
        {
            if ((ToWeymouth.Checked == true) || (ToLondon.Checked == true))
            {
                ActionDepart.Enabled    = true;
                ActionSet.Enabled       = true;
            }
        }

        private void ActionDepart_CheckedChanged(object sender, EventArgs e)
        {
            if (ActionDepart.Checked == true)
            {
                DesWey.Enabled = false;
                DesLon.Enabled = false;

            }
            else
            {
                DesWey.Enabled = true;
                DesLon.Enabled = true;
            }
            if (ActionSet.Checked == true)
            {
                DesWey.Enabled = true;
                DesLon.Enabled = true;
                DesPlat1.Enabled = true;
                DesPlat2.Enabled = true;
                TTbr47c1.Enabled = true;
                TTemu2.Enabled = true;
            }
            else
            {           
                DesWey.Enabled = false;
                DesLon.Enabled = false;
                DesPlat1.Enabled = false;
                DesPlat2.Enabled = false;
                TTbr47c1.Enabled = false;
                TTemu2.Enabled = false;

            }
            if ((ActionSet.Checked == true) || (ActionDepart.Checked == true))
            {
                OrgPlat1.Enabled = true;
                OrgPlat2.Enabled = true;
            }
            else
            {
                OrgPlat1.Enabled = false;
                OrgPlat2.Enabled = false;
            }
        }

        private void ActionSet_CheckedChanged(object sender, EventArgs e)
        {
            if (ActionDepart.Checked == true)
            {
                DesWey.Enabled = false;
                DesLon.Enabled = false;

            }
            else
            {
                DesWey.Enabled = true;
                DesLon.Enabled = true;
            }
            if (ActionSet.Checked == true)
            {
                DesWey.Enabled = true;
                DesLon.Enabled = true;
                DesPlat1.Enabled = true;
                DesPlat2.Enabled = true;
                TTbr47c1.Enabled = true;
                TTemu2.Enabled = true;
            }
            else
            {
                DesWey.Enabled = false;
                DesLon.Enabled = false;
                DesPlat1.Enabled = false;
                DesPlat2.Enabled = false;
                TTbr47c1.Enabled = false;
                TTemu2.Enabled = false;

            }
            if ((ActionSet.Checked == true) || (ActionDepart.Checked == true))
            {
                OrgPlat1.Enabled = true;
                OrgPlat2.Enabled = true;
            }
            else
            {
                OrgPlat1.Enabled = false;
                OrgPlat2.Enabled = false;
            }
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            ResetAll();
        }
        private void ResetAll()
        {
            ActionDepart.Enabled = false;
            ActionSet.Enabled = false;
            OrgPlat1.Enabled = false;
            OrgPlat2.Enabled = false;
            DesWey.Enabled = false;
            DesLon.Enabled = false;
            DesPlat1.Enabled = false;
            DesPlat2.Enabled = false;
            TTbr47c1.Enabled = false;
            TTemu2.Enabled = false;

            ActionDepart.Checked = false;
            ActionSet.Checked = false;
            OrgPlat1.Checked = false;
            OrgPlat2.Checked = false;
            DesWey.Checked = false;
            DesLon.Checked = false;
            DesPlat1.Checked = false;
            DesPlat2.Checked = false;
            TTbr47c1.Checked = false;
            TTemu2.Checked = false;
            ToLondon.Checked = false;
            ToWeymouth.Checked = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            send = "error";
            ResetAll();
        }
    }
}
