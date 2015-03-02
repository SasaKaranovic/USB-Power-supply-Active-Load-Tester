using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MySerialPortNamespace;
using System.Text.RegularExpressions;
using System.Globalization;
using System.Diagnostics;

namespace Power_supply_Active_Load_Tester
{

    

    public partial class Form1 : Form
    {
        

        SerialPortClass serialport = new SerialPortClass();

        public double latestVoltage = 0.00;
        public double latestCurrent = 0.00;
        public double latestOpAmp = 0.00;

        public bool AddToLog = true;

        Form2 Form2 = new Form2();


        //List Available ComPorts in Drop Down Box
        private void ListAvailablePorts() {
            dropPortSelect.Items.Clear();

            List<string> ComPorts = serialport.ListAvailablePorts();

            foreach (string port in ComPorts)
            {
                dropPortSelect.Items.Add(port);
            }

            dropPortSelect.SelectedIndex = dropPortSelect.Items.Count - 1;
            //dropPortSelect.SelectedIndex = 0;
        }

        //Parse Serial Port data using RegEx to get PSU Voltage
        public void ParseData(string data)
        {

            Debug.WriteLine("Working!");

            string strVoltage = null;
            string strCurrent = null;
            string strOpAmp   = null;

            double resultVoltage    = 0.00;
            double resultCurrent    = 0.00;
            double resultOpAmp      = 0.00;

            //Match Voltage and Current using RegEx
            //Voltage
            try
            {
                strVoltage = Regex.Match(data, "PSV:(?<voltage>[0-9.]{1,6})V", RegexOptions.Singleline | RegexOptions.IgnoreCase | RegexOptions.Multiline).Groups["voltage"].Value;
            }
            catch (Exception e)
            {
                Console.WriteLine("REGEX EXCEPTION Voltage: " + e.Message);
                strVoltage = "0.00";
            }

            //Current
            try
            {
                strCurrent = Regex.Match(data, "PSI:(?<current>[0-9.]{1,6})A", RegexOptions.Singleline | RegexOptions.IgnoreCase | RegexOptions.Multiline).Groups["current"].Value;
            }
            catch (Exception e)
            {
                Console.WriteLine("REGEX EXCEPTION Current: " + e.Message);
                strCurrent = "0.00";
            }

            //OpAmp
            try
            {
                strOpAmp = Regex.Match(data, "OPA:(?<opamp>[0-9.]{1,6})V", RegexOptions.Singleline | RegexOptions.IgnoreCase | RegexOptions.Multiline).Groups["opamp"].Value;
            }
            catch (Exception e)
            {
                Console.WriteLine("REGEX EXCEPTION OpAmp: " + e.Message);
                strOpAmp = "0.00";
            }

            //Convert string to double
            try
            {
                resultVoltage = double.Parse(strVoltage, CultureInfo.InvariantCulture);
                resultCurrent = double.Parse(strCurrent, CultureInfo.InvariantCulture);
                resultOpAmp = double.Parse(strOpAmp, CultureInfo.InvariantCulture);
            }
            catch (Exception e)
            {
               Console.WriteLine("Parse Double Error:" + e.Message);
            }


            Debug.WriteLine("V:" + strVoltage + " A:" + strCurrent + " O:" + strOpAmp);
            Debug.WriteLine("V:" + String.Format("{0:0.00}", resultVoltage) + " A:" + String.Format("{0:0.00}", resultCurrent) + " O:" + String.Format("{0:0.00}", resultOpAmp));

            latestVoltage = resultVoltage;
            latestCurrent = resultCurrent;
            latestOpAmp = resultOpAmp;

            if (AddToLog)
            {
                Variables.BufferCurrent.Add(resultVoltage);
                Variables.BufferVoltage.Add(latestCurrent);
                Variables.BufferOpAmp.Add(resultOpAmp);
            }
            

        }

        private bool AddToVoltage(Int32 targetmiliamps)
        {
            AddToLog = true;
            Int32 miliamps = 0;
            bool isNumber = Int32.TryParse(txtCurrent.Text.Trim(), out miliamps);

            miliamps = miliamps + targetmiliamps;


            if (isNumber == true && miliamps <= 5000)
            {

                string command = string.Format("S:{0:0000}", miliamps);
                Debug.WriteLine(command);


                serialport.Write(command);

                txtCurrent.Text = Convert.ToString(miliamps);

                return true;
            }
            else
            {
                MessageBox.Show("Current value must be a NUMERIC value.\n\rGiven in miliamps and ranging from 0 to 5000", "Miliamps value error");
                return false;
            }

        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ListAvailablePorts();

            serialport.SerialReadDone += new MySerialPortNamespace.SerialPortClass.MyEventHandler(ParseData);
        }

        private void Form1_Closing(object sender, EventArgs e)
        {
            serialport.Write("S:0000");
            serialport.PortClose();

            Form2.Close();
        }

        private void btnRead_Click(object sender, EventArgs e)
        {
            serialport.Write("C:O000");
            
            //string voltage = String.Format("{0:0.00}", SerialParseVoltage(SerialBuffer));
            //string current = String.Format("{0:0.00}", SerialParseCurrent(SerialBuffer));


            //lblVoltage.Text = "Voltage: " + voltage + "V";
            //lblCurrent.Text = "Current: " + current + "A";

        }

        private void btnOpenPort_Click(object sender, EventArgs e)
        {
            if (serialport.IsPortOpen() == true)
            {
                serialport.Write("S:0000");
                serialport.PortClose();
                btnOpenPort.Text = "Connect";
            }
            else
            {
                serialport.PortName = dropPortSelect.SelectedItem.ToString();
                serialport.BaudRate = 57600;

                if (serialport.PortOpen() == true) 
                {
                    btnOpenPort.Text = "Disconnect";
                }
                
            }
            
        }

        private void btnSetCurrent_Click(object sender, EventArgs e)
        {
            AddToLog = true;
            Int32 miliamps = 0;
            bool isNumber = Int32.TryParse(txtCurrent.Text.Trim(), out miliamps);


            if (isNumber == true && miliamps <= 5000)
            {
                string command = string.Format("S:{0:0000}", miliamps);
                Debug.WriteLine(command);
                

                serialport.Write(command);
            }
            else
            {
                MessageBox.Show("Current value must be a NUMERIC value.\n\rGiven in miliamps and ranging from 0 to 5000", "Miliamps value error");
            } 

        }

        private void btnRefreshPorts_Click(object sender, EventArgs e)
        {
            ListAvailablePorts();
        }

        private void lblRefresh_Tick(object sender, EventArgs e)
        {
            lblCurrent.Text = "Current: " + string.Format("{0:0.00}", latestCurrent);
            lblVoltage.Text = "Voltage: " + string.Format("{0:0.00}", latestVoltage);
            lblOpAmp.Text = "OpAmp: " + string.Format("{0:0.00}", latestOpAmp);
        }

        private void btnGraph_Click(object sender, EventArgs e)
        {
            Form2 Form2 = new Form2();
            Form2.Show();
        }

        private void btnCurrentOff_Click(object sender, EventArgs e)
        {
            AddToLog = false;
            serialport.Write("S:0000");


        }

        private void btn10mA_Click(object sender, EventArgs e)
        {
            AddToVoltage(10);
        }

        private void btn50mA_Click(object sender, EventArgs e)
        {
            AddToVoltage(50);
        }

        private void btn100mA_Click(object sender, EventArgs e)
        {
            AddToVoltage(100);
        }

        private void btn500mA_Click(object sender, EventArgs e)
        {
            AddToVoltage(500);
        }

        private void btnClearGraph_Click(object sender, EventArgs e)
        {
            Variables.BufferOpAmp.Clear();
            Variables.BufferCurrent.Clear();
            Variables.BufferVoltage.Clear();
        }


        
    }
}
