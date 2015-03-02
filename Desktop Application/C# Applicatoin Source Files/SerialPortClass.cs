using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Threading;


namespace MySerialPortNamespace
{
    class SerialPortClass
    {
        public SerialPort comPort = new SerialPort();
        private string strPing;
        private string strOpening;
        private string strClosing;
        private string strReturnToken;

        public delegate void MyEventHandler(string foo);
        public event MyEventHandler SerialReadDone;



        public SerialPortClass(string portName = "com1", int baudrate = 9600, string ping = "*ping*", string opening = "*open*", string closing = "*close*", string returnToken = ">", System.IO.Ports.Parity parity = System.IO.Ports.Parity.None, int dataBits = 8, System.IO.Ports.StopBits stopBits = System.IO.Ports.StopBits.One)
        {
            //Assign initial values aquired trough class creation
            this.strPing        = ping;
            this.strOpening     = opening;
            this.strClosing     = closing;
            this.strReturnToken = returnToken;

            //Create new serial port
            try
            {
                comPort = new SerialPort(portName, baudrate, parity, dataBits, stopBits);
                comPort.NewLine = strReturnToken;
                comPort.ReadTimeout = 1000;
                comPort.RtsEnable = false;
                comPort.DtrEnable = false;
                comPort.DataReceived += new SerialDataReceivedEventHandler(comPort_DataReceived);
            }
            catch (Exception e)
            {
                comPort = null;
                MessageBox.Show("Unhandled exception has occured: " + e.Message);
                Debug.WriteLine("Unhandled exception in SerialPortClass(): " + e.Message);
                //throw;
            }
        }


        //Return list of available serial ports
        public List<string> ListAvailablePorts()
        {
            List<string> serialports = new List<String>();

            try
            {
                foreach (String portName in System.IO.Ports.SerialPort.GetPortNames())
                {
                    serialports.Add(portName);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show("Could not get list of avalable serial porst.");
                Debug.WriteLine("Unhandled exception in ListAvailablePorts(): " + e.Message);
            }



            return serialports;
        }


        //Set the name of the COM port to use
        public string PortName
        {
            get { return comPort.PortName; }
            set 
            {
                if (comPort.IsOpen)
                {
                    comPort.Close();
                }
                comPort.PortName = value;
            }
            
        }

        public int BaudRate
        {
            get { return this.comPort.BaudRate;  }
            set
            {
                try
                {
                    this.comPort.BaudRate = value;
                }
                catch (Exception e)
                {
                    MessageBox.Show("Could not change baudrate for serial port " + comPort.PortName);
                    Debug.WriteLine("Could not change baudrate for serial port" + comPort.PortName + "." + e.Message);
                }
            }
        }

        //(re)Open serial port [used to open serial port or reopen after changing name/baudrate and etc]
        public bool PortOpen()
        {
            if (comPort.IsOpen)
            {
                try
                {
                    comPort.Close();
                }
                catch (Exception e)
                {
                    MessageBox.Show("Could not close/reopen serial port: " + comPort.PortName);
                    Debug.WriteLine("Could not close/reopen serial port:" + comPort.PortName + "." + e.Message);
                    return false;
                }
                
            }

            try
            {
                comPort.Open();
            }
            catch (Exception e)
            {
                MessageBox.Show("Could not open serial port: " + comPort.PortName);
                Debug.WriteLine("Could not open serial port:" + comPort.PortName + "." + e.Message);
                return false;
            }

            return true;

        }


        //Check if com port is open
        public bool IsPortOpen()
        {
            return comPort.IsOpen;
        }


        //Close ComPort
        public bool PortClose()
        {
            if (comPort.IsOpen)
            {
                try
                {
                    comPort.Close();
                }
                catch (Exception e)
                {
                    MessageBox.Show("Could not close serial port: " + comPort.PortName);
                    Debug.WriteLine("Could not close serial port:" + comPort.PortName + "." + e.Message);
                    return false;
                }
            }
            else { return false; }

            return true;
        }


        //write to serial port
        public bool Write(String data)
        {
            if (comPort.IsOpen)
            {
                try
                {
                    comPort.WriteLine(data);
                }
                catch (Exception e)
                {
                    MessageBox.Show("Could not write to serial port: " + comPort.PortName);
                    Debug.WriteLine("Could not write to serial port:" + comPort.PortName + "." + e.Message);
                    return false;
                }
            }
            else { return false; }

            return true;
        }


        //read from serial port
        public string ReadLine()
        {
            String line = "";

            if (comPort.IsOpen)
            {
                try
                {
                    line = comPort.ReadLine();
                }
                catch (Exception e)
                {
                    MessageBox.Show("Could not read from serial port: " + comPort.PortName);
                    Console.WriteLine("Could not read from serial port:" + comPort.PortName + "." + e.Message);
                    return null;
                }
            }
            else { return null; }

            return line;
        }

        //Read from serial port
        public string Read()
        {

             String line = "";

            if (comPort.IsOpen)
            {
                try
                {
                    //char[] read;
                    //comPort.Read(read, 0, comPort.ReadBufferSize);
                    
                }
                catch (Exception e)
                {
                    MessageBox.Show("Could not read from serial port: " + comPort.PortName);
                    Debug.WriteLine("Could not read from serial port:" + comPort.PortName + "." + e.Message);
                    return null;
                }
            }
            else { return null; }

            return line;
        }

        public void comPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort port = (SerialPort)sender;

            Debug.WriteLine("Serial Receive data fired!");

            Thread.Sleep(500);

            int ByteToRead = port.BytesToRead;
            char[] inputData = new char[ByteToRead];

            port.Read(inputData, 0, port.BytesToRead);

            string OutputString = new string(inputData);

            OutputString = OutputString.Replace(System.Environment.NewLine, " ");

            Debug.WriteLine(OutputString);

            SerialReadDone.Invoke(OutputString);
            
        }

    }
}
