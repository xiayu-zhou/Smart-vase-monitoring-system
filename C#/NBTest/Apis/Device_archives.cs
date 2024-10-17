using AepSdk.Apis.Core;
using System.Collections.Generic;


namespace AepSdk.Apis
{
    class Device_archives
    {
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string DeleteArchivesInfo(string appKey, string appSecret, string body)
        {
            string path = "/device_archives/deleteArchivesInfo";
            Dictionary<string, string> headers = null;
            Dictionary<string, string> param = null;
            string version = "20231117042743";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "POST");
            if (response != null)
                return response;
            return null;
        }
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string GetArchivesAttribute(string appKey, string appSecret, string body)
        {
            string path = "/device_archives/getArchivesAttr";
            Dictionary<string, string> headers = null;
            Dictionary<string, string> param = null;
            string version = "20231117042748";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "POST");
            if (response != null)
                return response;
            return null;
        }
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string UpdateArchivesInfo(string appKey, string appSecret, string body)
        {
            string path = "/device_archives/updateArchivesInfo";
            Dictionary<string, string> headers = null;
            Dictionary<string, string> param = null;
            string version = "20231117042738";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "POST");
            if (response != null)
                return response;
            return null;
        }
        //参数productId: 类型long, 参数不可以为空
        //  描述:
        //参数deviceId: 类型String, 参数不可以为空
        //  描述:
        public static string GetArchivesInfoDetailById(string appKey, string appSecret, string productId, string deviceId)
        {
            string path = "/device_archives/getArchivesInfoDetailById";
            Dictionary<string, string> headers = null;
            Dictionary<string, string> param = new Dictionary<string, string>();
            param.Add("productId", productId);
            param.Add("deviceId", deviceId);

            string version = "20231117042731";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, null, version, application, key, "GET");
            if (response != null)
                return response;
            return null;
        }

    }
}
