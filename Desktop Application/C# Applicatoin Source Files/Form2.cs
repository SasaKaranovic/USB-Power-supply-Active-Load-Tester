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

using System.Windows.Forms.DataVisualization.Charting;
using Power_supply_Active_Load_Tester;


namespace Power_supply_Active_Load_Tester
{
    public partial class Form2 : Form
    {
       

        public Form2()
        {
            InitializeComponent();
        }


        void Form2_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            
        }

        private void Form2_Load(object sender, EventArgs e)
        {

            Series Measured = new Series("measured");

            


            for (int i = 0; i < Variables.BufferVoltage.Count; i++)
            {
                double yval = Variables.BufferCurrent[i];
                double xval = Variables.BufferVoltage[i];

                Measured.Points.AddXY(xval, yval);
                Debug.WriteLine("Voltage: " + xval + "\tCurrent: " + yval);
            }

            

            //Chart Appereance
            Measured.ChartType = SeriesChartType.Spline;
            Measured.Palette = ChartColorPalette.EarthTones;
            Measured.IsValueShownAsLabel = true;

           

            chart1.Series.Add(Measured);

            chart1.ChartAreas[0].AxisY.IsStartedFromZero = false;
            chart1.ChartAreas[0].RecalculateAxesScale();

            chart1.ChartAreas[0].AxisY.Title = "Voltage [V]";
            chart1.ChartAreas[0].AxisX.Title = "Current [A]";


        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void chart1_DoubleClick(object sender, System.EventArgs e)
        {
            DateTime time = DateTime.Now;
            string filename = time.ToString("yyyy-MM-dd-HH-mm") + "-chart.png";

            try
            {
                this.chart1.SaveImage("C:\\" + filename, ChartImageFormat.Png);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            
        }
    }
}
