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


        private void ChartRedraw(SeriesChartType ChartType = SeriesChartType.Spline, ChartColorPalette Pallete = ChartColorPalette.EarthTones)
        {
            chart1.Series.Clear();

            Series Measured = new Series("measured");

            for (int i = 0; i < Variables.BufferVoltage.Count; i++)
            {
                double yval = Variables.BufferCurrent[i];
                double xval = Variables.BufferVoltage[i];

                Measured.Points.AddXY(xval, yval);
                Debug.WriteLine("Voltage: " + xval + "\tCurrent: " + yval);
            }


            //Chart Appereance
            Measured.ChartType = ChartType;
            Measured.Palette = Pallete;
            Measured.IsValueShownAsLabel = true;



            chart1.Series.Add(Measured);

            chart1.ChartAreas[0].AxisY.IsStartedFromZero = false;
            chart1.ChartAreas[0].RecalculateAxesScale();

            chart1.ChartAreas[0].AxisY.Title = "Voltage [V]";
            chart1.ChartAreas[0].AxisX.Title = "Current [A]";
            chart1.ChartAreas[0].AxisX.LabelStyle.Format = "{0:0.000}";
        }

        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            ChartRedraw();
        }

        private void lineToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ChartRedraw(SeriesChartType.Line);
        }

        private void splineToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ChartRedraw(SeriesChartType.Spline);
        }

        private void pointsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ChartRedraw(SeriesChartType.Point);
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DateTime time = DateTime.Now;
            string filename = time.ToString("yyyy-MM-dd-HH-mm") + "-chart.png";

            // Displays a SaveFileDialog so the user can save the Image
           // assigned to Button2.
           SaveFileDialog saveFileDialog1 = new SaveFileDialog();
           saveFileDialog1.Filter = "PNG Image|*.png";
           saveFileDialog1.Title = "Save an Image File";
           saveFileDialog1.FileName = filename;
           saveFileDialog1.ShowDialog();

           // If the file name is not an empty string open it for saving.
           if(saveFileDialog1.FileName != "")
           {

               try
               {
                   this.chart1.SaveImage(saveFileDialog1.FileName, ChartImageFormat.Png);
               }
               catch (Exception ex)
               {
                   Console.WriteLine(ex.Message);
               }
            }



        }

        private void clearChartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var confirmed = MessageBox.Show("Delete all of the previously logged data?", "Confirm Clear Graph", MessageBoxButtons.YesNoCancel);

            if (confirmed == DialogResult.Yes)
            {
                Variables.BufferOpAmp.Clear();
                Variables.BufferCurrent.Clear();
                Variables.BufferVoltage.Clear();
                MessageBox.Show("Graph cleared!");
            }
        }

    }
}
