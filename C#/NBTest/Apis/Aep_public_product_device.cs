using AepSdk.Apis.Core;
using System.Collections.Generic;


namespace AepSdk.Apis
{
    class Aep_public_product_device
    {
        //参数MasterKey: 类型String, 参数不可以为空
        //  描述:公共产品的MasterKey
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string QueryDeviceToken(string appKey, string appSecret, string MasterKey, string body)
        {
            string path = "/aep_public_product_device/queryDeviceToken";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = null;
            string version = "20230330172346";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "POST");
            if (response != null)
                return response;
            return null;
        }

    }
}
