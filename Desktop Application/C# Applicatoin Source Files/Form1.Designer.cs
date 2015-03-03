namespace Power_supply_Active_Load_Tester
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btnRead = new System.Windows.Forms.Button();
            this.btnOpenPort = new System.Windows.Forms.Button();
            this.btnSetCurrent = new System.Windows.Forms.Button();
            this.dropPortSelect = new System.Windows.Forms.ComboBox();
            this.btnRefreshPorts = new System.Windows.Forms.Button();
            this.lblVoltage = new System.Windows.Forms.Label();
            this.lblCurrent = new System.Windows.Forms.Label();
            this.lblRefresh = new System.Windows.Forms.Timer(this.components);
            this.lblOpAmp = new System.Windows.Forms.Label();
            this.btnGraph = new System.Windows.Forms.Button();
            this.btnCurrentOff = new System.Windows.Forms.Button();
            this.txtCurrent = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btn10mA = new System.Windows.Forms.Button();
            this.btn50mA = new System.Windows.Forms.Button();
            this.btn100mA = new System.Windows.Forms.Button();
            this.btn500mA = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnRead
            // 
            this.btnRead.Location = new System.Drawing.Point(230, 105);
            this.btnRead.Name = "btnRead";
            this.btnRead.Size = new System.Drawing.Size(96, 23);
            this.btnRead.TabIndex = 0;
            this.btnRead.Text = "Read Values";
            this.btnRead.UseVisualStyleBackColor = true;
            this.btnRead.Click += new System.EventHandler(this.btnRead_Click);
            // 
            // btnOpenPort
            // 
            this.btnOpenPort.Location = new System.Drawing.Point(118, 12);
            this.btnOpenPort.Name = "btnOpenPort";
            this.btnOpenPort.Size = new System.Drawing.Size(75, 23);
            this.btnOpenPort.TabIndex = 3;
            this.btnOpenPort.Text = "Open Port";
            this.btnOpenPort.UseVisualStyleBackColor = true;
            this.btnOpenPort.Click += new System.EventHandler(this.btnOpenPort_Click);
            // 
            // btnSetCurrent
            // 
            this.btnSetCurrent.Location = new System.Drawing.Point(230, 76);
            this.btnSetCurrent.Name = "btnSetCurrent";
            this.btnSetCurrent.Size = new System.Drawing.Size(96, 23);
            this.btnSetCurrent.TabIndex = 4;
            this.btnSetCurrent.Text = "Set Current Draw";
            this.btnSetCurrent.UseVisualStyleBackColor = true;
            this.btnSetCurrent.Click += new System.EventHandler(this.btnSetCurrent_Click);
            // 
            // dropPortSelect
            // 
            this.dropPortSelect.FormattingEnabled = true;
            this.dropPortSelect.Location = new System.Drawing.Point(12, 14);
            this.dropPortSelect.Name = "dropPortSelect";
            this.dropPortSelect.Size = new System.Drawing.Size(100, 21);
            this.dropPortSelect.TabIndex = 5;
            // 
            // btnRefreshPorts
            // 
            this.btnRefreshPorts.Location = new System.Drawing.Point(199, 12);
            this.btnRefreshPorts.Name = "btnRefreshPorts";
            this.btnRefreshPorts.Size = new System.Drawing.Size(75, 23);
            this.btnRefreshPorts.TabIndex = 6;
            this.btnRefreshPorts.Text = "Refresh list";
            this.btnRefreshPorts.UseVisualStyleBackColor = true;
            this.btnRefreshPorts.Click += new System.EventHandler(this.btnRefreshPorts_Click);
            // 
            // lblVoltage
            // 
            this.lblVoltage.AutoSize = true;
            this.lblVoltage.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblVoltage.Location = new System.Drawing.Point(14, 53);
            this.lblVoltage.Name = "lblVoltage";
            this.lblVoltage.Size = new System.Drawing.Size(81, 20);
            this.lblVoltage.TabIndex = 8;
            this.lblVoltage.Text = "Voltage: ";
            // 
            // lblCurrent
            // 
            this.lblCurrent.AutoSize = true;
            this.lblCurrent.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCurrent.Location = new System.Drawing.Point(14, 79);
            this.lblCurrent.Name = "lblCurrent";
            this.lblCurrent.Size = new System.Drawing.Size(79, 20);
            this.lblCurrent.TabIndex = 9;
            this.lblCurrent.Text = "Current: ";
            // 
            // lblRefresh
            // 
            this.lblRefresh.Enabled = true;
            this.lblRefresh.Tick += new System.EventHandler(this.lblRefresh_Tick);
            // 
            // lblOpAmp
            // 
            this.lblOpAmp.AutoSize = true;
            this.lblOpAmp.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblOpAmp.Location = new System.Drawing.Point(14, 105);
            this.lblOpAmp.Name = "lblOpAmp";
            this.lblOpAmp.Size = new System.Drawing.Size(78, 20);
            this.lblOpAmp.TabIndex = 10;
            this.lblOpAmp.Text = "OpAmp: ";
            // 
            // btnGraph
            // 
            this.btnGraph.Location = new System.Drawing.Point(12, 229);
            this.btnGraph.Name = "btnGraph";
            this.btnGraph.Size = new System.Drawing.Size(318, 23);
            this.btnGraph.TabIndex = 11;
            this.btnGraph.Text = "Display Graph";
            this.btnGraph.UseVisualStyleBackColor = true;
            this.btnGraph.Click += new System.EventHandler(this.btnGraph_Click);
            // 
            // btnCurrentOff
            // 
            this.btnCurrentOff.Location = new System.Drawing.Point(230, 134);
            this.btnCurrentOff.Name = "btnCurrentOff";
            this.btnCurrentOff.Size = new System.Drawing.Size(96, 23);
            this.btnCurrentOff.TabIndex = 12;
            this.btnCurrentOff.Text = "Current Off";
            this.btnCurrentOff.UseVisualStyleBackColor = true;
            this.btnCurrentOff.Click += new System.EventHandler(this.btnCurrentOff_Click);
            // 
            // txtCurrent
            // 
            this.txtCurrent.Location = new System.Drawing.Point(230, 50);
            this.txtCurrent.MaxLength = 4;
            this.txtCurrent.Name = "txtCurrent";
            this.txtCurrent.Size = new System.Drawing.Size(80, 20);
            this.txtCurrent.TabIndex = 13;
            this.txtCurrent.Text = "0";
            this.txtCurrent.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(308, 53);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(22, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "mA";
            // 
            // btn10mA
            // 
            this.btn10mA.Location = new System.Drawing.Point(12, 163);
            this.btn10mA.Name = "btn10mA";
            this.btn10mA.Size = new System.Drawing.Size(75, 23);
            this.btn10mA.TabIndex = 16;
            this.btn10mA.Text = "+10mA";
            this.btn10mA.UseVisualStyleBackColor = true;
            this.btn10mA.Click += new System.EventHandler(this.btn10mA_Click);
            // 
            // btn50mA
            // 
            this.btn50mA.Location = new System.Drawing.Point(93, 163);
            this.btn50mA.Name = "btn50mA";
            this.btn50mA.Size = new System.Drawing.Size(75, 23);
            this.btn50mA.TabIndex = 17;
            this.btn50mA.Text = "+50mA";
            this.btn50mA.UseVisualStyleBackColor = true;
            this.btn50mA.Click += new System.EventHandler(this.btn50mA_Click);
            // 
            // btn100mA
            // 
            this.btn100mA.Location = new System.Drawing.Point(174, 163);
            this.btn100mA.Name = "btn100mA";
            this.btn100mA.Size = new System.Drawing.Size(75, 23);
            this.btn100mA.TabIndex = 18;
            this.btn100mA.Text = "+100mA";
            this.btn100mA.UseVisualStyleBackColor = true;
            this.btn100mA.Click += new System.EventHandler(this.btn100mA_Click);
            // 
            // btn500mA
            // 
            this.btn500mA.Location = new System.Drawing.Point(255, 163);
            this.btn500mA.Name = "btn500mA";
            this.btn500mA.Size = new System.Drawing.Size(75, 23);
            this.btn500mA.TabIndex = 19;
            this.btn500mA.Text = "+500mA";
            this.btn500mA.UseVisualStyleBackColor = true;
            this.btn500mA.Click += new System.EventHandler(this.btn500mA_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(338, 264);
            this.Controls.Add(this.btn500mA);
            this.Controls.Add(this.btn100mA);
            this.Controls.Add(this.btn50mA);
            this.Controls.Add(this.btn10mA);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtCurrent);
            this.Controls.Add(this.btnCurrentOff);
            this.Controls.Add(this.btnGraph);
            this.Controls.Add(this.lblOpAmp);
            this.Controls.Add(this.lblCurrent);
            this.Controls.Add(this.lblVoltage);
            this.Controls.Add(this.btnRefreshPorts);
            this.Controls.Add(this.dropPortSelect);
            this.Controls.Add(this.btnSetCurrent);
            this.Controls.Add(this.btnOpenPort);
            this.Controls.Add(this.btnRead);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Power Supply Active Load v0.6.1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnRead;
        private System.Windows.Forms.Button btnOpenPort;
        private System.Windows.Forms.Button btnSetCurrent;
        private System.Windows.Forms.ComboBox dropPortSelect;
        private System.Windows.Forms.Button btnRefreshPorts;
        public System.Windows.Forms.Label lblVoltage;
        public System.Windows.Forms.Label lblCurrent;
        private System.Windows.Forms.Timer lblRefresh;
        public System.Windows.Forms.Label lblOpAmp;
        private System.Windows.Forms.Button btnGraph;
        private System.Windows.Forms.Button btnCurrentOff;
        private System.Windows.Forms.TextBox txtCurrent;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn10mA;
        private System.Windows.Forms.Button btn50mA;
        private System.Windows.Forms.Button btn100mA;
        private System.Windows.Forms.Button btn500mA;
    }
}

