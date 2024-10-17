using AepSdk.Apis;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.Windows.Forms.DataVisualization.Charting;
using Newtonsoft.Json.Linq;

namespace NBTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 下发指令
        /// </summary>
        /// <param name="serviceIdentifier">服务的标识</param>
        /// <param name="shuxin">属性的表示</param>
        /// <param name="value">发送的值</param>
        /// <param name="operoperator">操作人员</param>
        void sendComd(string serviceIdentifier,string shuxin,int value,string operoperator)
        {
            string result = null;
            string body = "{\"content\":{\"params\":{\"" + shuxin + "\":" + value +
                "},\"serviceIdentifier\":\"" + serviceIdentifier + "\"},\"deviceId\":\"90530cf5823143c6a18fd4a2348f6b66\",\"operator\":\""
                + operoperator + "\",\"productId\":17017285}";
            result = Aep_device_command.CreateCommand("HU6Obfg4Qm4", "MrFB2K6L9L", "99bb0d21900b4157bff8ba5bd3ca0750", body);
            Console.WriteLine("result = " + result);
        }

        /// <summary>
        /// 设置温度
        /// </summary>
        /// <param name="temp">温度</param>
        void setTemp(string temp)
        {
            wendu_la.Text = "温度:" + temp + "℃";
        }

        /// <summary>
        /// 设置湿度
        /// </summary>
        /// <param name="hum">湿度</param>
        void setHum(string hum)
        {
            shidu_la.Text = "湿度:" + hum;
        }

        /// <summary>
        /// 设置二氧化碳
        /// </summary>
        /// <param name="co2"></param>
        void setCO2(string co2)
        {
            CO2_la.Text = "二氧化碳:" + co2 + "ppm";
        }

        /// <summary>
        /// 设置一氧化碳
        /// </summary>
        /// <param name="co"></param>
        void setCO(string co)
        {
            CO_la.Text= "一氧化碳:" + co + "ppm";
        }

        /// <summary>
        /// 设置氧气的浓度
        /// </summary>
        /// <param name="o2"></param>
        void setO2(string o2)
        {
            O2_la.Text = "氧气:" + o2;
        }

        /// <summary>
        /// 设置甲烷浓度
        /// </summary>
        /// <param name="ch4"></param>
        void setCH4(string ch4)
        {
            CH4_la.Text = "甲烷:" + ch4 + "ppm";
        }

        /// <summary>
        /// 设置土壤湿度
        /// </summary>
        /// <param name="tuHum"></param>
        void setTuHum(string tuHum)
        {
            tuhum_la.Text = "土壤湿度:" + tuHum;
        }

        /// <summary>
        /// 设置土壤含水量
        /// </summary>
        /// <param name="tuWater"></param>
        void setTuWater(string tuWater)
        {
            tuwater_la.Text = "土壤含氧量:" + tuWater;
        }

        /// <summary>
        /// 设置水位
        /// </summary>
        /// <param name="shuiWei"></param>
        void setShuiWei(string shuiWei)
        {
            sw_la.Text = "水位:" + shuiWei + "mm";
        }

        /// <summary>
        /// 温湿度折线图
        /// </summary>
        void wenShiduZheXianInit()
        {
            var chart = wendu_z.ChartAreas[0];
            chart.AxisX.IntervalType = DateTimeIntervalType.Number;

            chart.AxisX.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.IsEndLabelVisible = true;

            chart.AxisX.Minimum = 0;
            chart.AxisX.Maximum = 12;
            chart.AxisY.Minimum = -20;
            chart.AxisY.Maximum = 100;
            chart.AxisX.Interval = 1;
            chart.AxisY.Interval = 10;
            chart.AxisX.Enabled = AxisEnabled.True;//将X轴始终展示
            chart.AxisY.Enabled = AxisEnabled.True;//将Y轴始终展示

            wendu_z.Series.Add("温度");
            wendu_z.Series.Add("湿度");
            wendu_z.Series.Add("土壤湿度");
            wendu_z.Series.Add("土壤含氧量");

            //绘制折线图
            wendu_z.Series["温度"].ChartType = SeriesChartType.Line;
            wendu_z.Series["湿度"].ChartType = SeriesChartType.Line;
            wendu_z.Series["土壤湿度"].ChartType = SeriesChartType.Line;
            wendu_z.Series["土壤含氧量"].ChartType = SeriesChartType.Line;
            //绘制曲线图
            //wendu_z.Series["line1"].ChartType = SeriesChartType.Spline;
            wendu_z.Series["温度"].Color = Color.Red;
            wendu_z.Series["湿度"].Color = Color.Blue;
            wendu_z.Series["土壤湿度"].Color = Color.Green;
            wendu_z.Series["土壤含氧量"].Color = Color.Purple;
            wendu_z.Series[0].IsVisibleInLegend = true;
            wendu_z.Series[1].IsVisibleInLegend = true;
            wendu_z.Series[2].IsVisibleInLegend = true;
            wendu_z.Series[3].IsVisibleInLegend = true;
        }

        /// <summary>
        /// 添加数据到折线图
        /// </summary>
        /// <param name="tem"></param>
        /// <param name="value"></param>
        /// <param name="chart"></param>
        void addData(string tem,string value,Chart chart)
        {
            int num = chart.Series[tem].Points.Count;
            if(num > 12)
            {
                chart.Series[tem].Points.RemoveAt(0);
                for(int i = 0; i < num - 1;i++)
                {
                    chart.Series[tem].Points[i].XValue = i;
                }
            }
            chart.Series[tem].Points.AddXY(num, value);
        }

        /// <summary>
        /// 气体折线图
        /// </summary>
        void qiTiZheXianTuInit()
        {
            var chart = qiti_z.ChartAreas[0];
            chart.AxisX.IntervalType = DateTimeIntervalType.Number;

            chart.AxisX.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.IsEndLabelVisible = true;

            chart.AxisX.Minimum = 0;
            chart.AxisX.Maximum = 12;
            chart.AxisY.Minimum = 0;
            chart.AxisY.Maximum = 5000;
            chart.AxisX.Interval = 1;
            chart.AxisY.Interval = 200;
            chart.AxisX.Enabled = AxisEnabled.True;//将X轴始终展示
            chart.AxisY.Enabled = AxisEnabled.True;//将Y轴始终展示

            qiti_z.Series.Add("二氧化碳");
            qiti_z.Series.Add("一氧化碳");

            //绘制折线图
            qiti_z.Series["二氧化碳"].ChartType = SeriesChartType.Line;
            qiti_z.Series["一氧化碳"].ChartType = SeriesChartType.Line;
            //绘制曲线图
            //wendu_z.Series["line1"].ChartType = SeriesChartType.Spline;
            qiti_z.Series["二氧化碳"].Color = Color.Red;
            qiti_z.Series["一氧化碳"].Color = Color.Blue;
            qiti_z.Series[0].IsVisibleInLegend = true;
            qiti_z.Series[1].IsVisibleInLegend = true;
        }

        /// <summary>
        /// 甲烷折线图初始化
        /// </summary>
        void jiaWanZheXianTu()
        {
            var chart = CH4_z.ChartAreas[0];
            chart.AxisX.IntervalType = DateTimeIntervalType.Number;

            chart.AxisX.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.IsEndLabelVisible = true;

            chart.AxisX.Minimum = 0;
            chart.AxisX.Maximum = 12;
            chart.AxisY.Minimum = 0;
            chart.AxisY.Maximum = 60000;
            chart.AxisX.Interval = 1;
            chart.AxisY.Interval = 3000;
            chart.AxisX.Enabled = AxisEnabled.True;//将X轴始终展示
            chart.AxisY.Enabled = AxisEnabled.True;//将Y轴始终展示

            CH4_z.Series.Add("甲烷");

            //绘制折线图
            CH4_z.Series["甲烷"].ChartType = SeriesChartType.Line;
            //绘制曲线图
            //wendu_z.Series["line1"].ChartType = SeriesChartType.Spline;
            CH4_z.Series["甲烷"].Color = Color.Blue;
            CH4_z.Series[0].IsVisibleInLegend = true;
        }

        /// <summary>
        /// 其他折线图初始化
        /// </summary>
        void OZheXianTu()
        {
            var chart = O_z.ChartAreas[0];
            chart.AxisX.IntervalType = DateTimeIntervalType.Number;

            chart.AxisX.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.Format = "";
            chart.AxisY.LabelStyle.IsEndLabelVisible = true;

            chart.AxisX.Minimum = 0;
            chart.AxisX.Maximum = 12;
            chart.AxisY.Minimum = 0;
            chart.AxisY.Maximum = 100;
            chart.AxisX.Interval = 1;
            chart.AxisY.Interval = 10;
            chart.AxisX.Enabled = AxisEnabled.True;//将X轴始终展示
            chart.AxisY.Enabled = AxisEnabled.True;//将Y轴始终展示

            O_z.Series.Add("氧气浓度");
            O_z.Series.Add("水位");

            //绘制折线图
            O_z.Series["氧气浓度"].ChartType = SeriesChartType.Line;
            O_z.Series["水位"].ChartType = SeriesChartType.Line;
            O_z.Series["氧气浓度"].Color = Color.Blue;
            O_z.Series["水位"].Color = Color.Green;
            O_z.Series[0].IsVisibleInLegend = true;
            O_z.Series[1].IsVisibleInLegend = true;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            wenShiduZheXianInit();
            qiTiZheXianTuInit();
            jiaWanZheXianTu();
            OZheXianTu();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            sendComd("light", "openLight",0,"zxy");
        }

        private void Light1_Click(object sender, EventArgs e)
        {
            sendComd("light", "openLight", 25, "zxy");
        }

        private void Light2_Click(object sender, EventArgs e)
        {
            sendComd("light", "openLight", 50, "zxy");
        }

        private void Light3_Click(object sender, EventArgs e)
        {
            sendComd("light", "openLight", 75, "zxy");
        }

        private void Light4_Click(object sender, EventArgs e)
        {
            sendComd("light", "openLight", 100, "zxy");
        }

        private void fen_off_Click(object sender, EventArgs e)
        {
            sendComd("fen", "drvm", 0, "zxy");
        }

        private void fen1_Click(object sender, EventArgs e)
        {
            sendComd("fen", "drvm", 25, "zxy");
        }

        private void fen2_Click(object sender, EventArgs e)
        {
            sendComd("fen", "drvm", 50, "zxy");
        }

        private void fen3_Click(object sender, EventArgs e)
        {
            sendComd("fen", "drvm", 75, "zxy");
        }

        private void fen4_Click(object sender, EventArgs e)
        {
            sendComd("fen", "drvm", 100, "zxy");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            sendComd("js", "jiaoshui", 1, "zxy");
            //addData("温度", "40", wendu_z);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            sendComd("js", "jiaoshui", 0, "zxy");
        }

        /// <summary>
        /// 定时器触发事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1_Tick(object sender, EventArgs e)
        {
            string result;
            string body = "{\"productId\":\"17017285\",\"deviceId\":\"90530cf5823143c6a18fd4a2348f6b66\"}";
            result = Aep_device_status.QueryDeviceStatusList("HU6Obfg4Qm4", "MrFB2K6L9L", body);
            Console.WriteLine("result = " + result);

            Data data = JsonConvert.DeserializeObject<Data>(result);
            foreach (var item in data.deviceStatusList)
            {
                if (item.datasetId.Equals("temp"))
                {
                    setTemp(item.value);
                    addData("温度",item.value,wendu_z);
                }
                else if (item.datasetId.Equals("huim"))
                {
                    setHum(item.value);
                    addData("湿度", item.value, wendu_z);
                }
                else if (item.datasetId.Equals("O2"))
                {
                    setO2(item.value);
                    addData("氧气浓度", item.value, O_z);
                }
                else if (item.datasetId.Equals("CO2"))
                {
                    setCO2(item.value);
                    addData("二氧化碳", item.value, qiti_z);
                }
                else if (item.datasetId.Equals("CO"))
                {
                    setCO(item.value);
                    addData("一氧化碳", item.value, qiti_z);
                }
                else if (item.datasetId.Equals("CH4"))
                {
                    setCH4(item.value);
                    addData("甲烷", item.value, CH4_z);
                }
                else if (item.datasetId.Equals("water"))
                {
                    setTuWater(item.value);
                    addData("土壤含氧量", item.value, wendu_z);
                }
                else if (item.datasetId.Equals("waterwei"))
                {
                    setShuiWei(item.value);
                    addData("水位", item.value, O_z);
                }
                else if (item.datasetId.Equals("tuhuim"))
                {
                    setTuHum(item.value);
                    addData("土壤湿度", item.value, wendu_z);
                }
            }
        }
    }
    /// <summary>
    /// 数据
    /// </summary>
    public class Data
    {
        public string code { get; set; }
        public List<DeviceStatusList> deviceStatusList { get; set; }
        public string desc { get; set; }
    }
    /// <summary>
    /// 每一个服务的数据
    /// </summary>
    public class DeviceStatusList
    {
        public string value { get; set; }
        public string timestamp { get; set; }
        public string datasetId { get; set; }
    }
}
