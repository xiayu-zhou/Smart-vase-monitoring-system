using AepSdk.Apis.Core;
using System.Collections.Generic;


namespace AepSdk.Apis
{
    class Aep_device_command_cancel
    {
        //参数MasterKey: 类型String, 参数不可以为空
        //  描述:
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string CancelAllCommand(string appKey, string appSecret, string MasterKey, string body)
        {
            string path = "/aep_device_command_cancel/cancelAllCommand";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = null;
            string version = "20230419143717";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "PUT");
            if (response != null)
                return response;
            return null;
        }

    }
}
