using AepSdk.Apis.Core;
using System.Collections.Generic;


namespace AepSdk.Apis
{
    class Aep_nb_device_management
    {
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string BatchCreateNBDevice(string appKey, string appSecret, string body)
        {
            string path = "/aep_nb_device_management/batchNBDevice";
            Dictionary<string, string> headers = null;
            Dictionary<string, string> param = null;
            string version = "20200828140355";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "POST");
            if (response != null)
                return response;
            return null;
        }
        //参数MasterKey: 类型String, 参数不可以为空
        //  描述:
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string BatchCancelDevices(string appKey, string appSecret, string MasterKey, string body)
        {
            string path = "/aep_nb_device_management/cancelledDevices";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = null;
            string version = "20211009093738";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "PUT");
            if (response != null)
                return response;
            return null;
        }
        //参数MasterKey: 类型String, 参数不可以为空
        //  描述:
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string DeleteDeviceByImei(string appKey, string appSecret, string MasterKey, string body)
        {
            string path = "/aep_nb_device_management/deleteDeviceByImei";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = null;
            string version = "20220226071405";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "POST");
            if (response != null)
                return response;
            return null;
        }
        //参数productId: 类型long, 参数不可以为空
        //  描述:
        //参数imei: 类型String, 参数不可以为空
        //  描述:
        //参数MasterKey: 类型String, 参数不可以为空
        //  描述:
        public static string QueryDeviceByImei(string appKey, string appSecret, string productId, string imei, string MasterKey)
        {
            string path = "/aep_nb_device_management/getDeviceByImei";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = new Dictionary<string, string>();
            param.Add("productId", productId);
            param.Add("imei", imei);

            string version = "20221130175656";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, null, version, application, key, "GET");
            if (response != null)
                return response;
            return null;
        }

    }
}
