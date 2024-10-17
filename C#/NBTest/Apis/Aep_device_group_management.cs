using AepSdk.Apis.Core;
using System.Collections.Generic;


namespace AepSdk.Apis
{
    class Aep_device_group_management
    {
        //参数MasterKey: 类型String, 参数可以为空
        //  描述:
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string CreateDeviceGroup(string appKey, string appSecret, string body, string MasterKey = "")
        {
            string path = "/aep_device_group_management/deviceGroup";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = null;
            string version = "20190615001622";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "POST");
            if (response != null)
                return response;
            return null;
        }
        //参数MasterKey: 类型String, 参数可以为空
        //  描述:
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string UpdateDeviceGroup(string appKey, string appSecret, string body, string MasterKey = "")
        {
            string path = "/aep_device_group_management/deviceGroup";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = null;
            string version = "20190615001615";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "PUT");
            if (response != null)
                return response;
            return null;
        }
        //参数productId: 类型long, 参数可以为空
        //  描述:产品Id，单产品分组必填
        //参数deviceGroupId: 类型long, 参数不可以为空
        //  描述:分组Id
        //参数MasterKey: 类型String, 参数可以为空
        //  描述:
        public static string DeleteDeviceGroup(string appKey, string appSecret, string deviceGroupId, string productId = "", string MasterKey = "")
        {
            string path = "/aep_device_group_management/deviceGroup";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = new Dictionary<string, string>();
            param.Add("productId", productId);
            param.Add("deviceGroupId", deviceGroupId);

            string version = "20190615001601";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, null, version, application, key, "DELETE");
            if (response != null)
                return response;
            return null;
        }
        //参数pageNow: 类型long, 参数不可以为空
        //  描述:当前页数
        //参数pageSize: 类型long, 参数不可以为空
        //  描述:每页记录数
        //参数productId: 类型long, 参数可以为空
        //  描述:支持通过产品id查询单产品分组列表
        //参数deviceGroupId: 类型long, 参数可以为空
        //  描述:支持通过分组ID查询
        //参数deviceGroupName: 类型String, 参数可以为空
        //  描述:支持通过分组名称查询
        //参数groupLevel: 类型long, 参数可以为空
        //  描述:支持通过分组类别查询，0为单产品分组，1为多产品分组
        public static string QueryDeviceGroupList(string appKey, string appSecret, string pageNow, string pageSize, string productId = "", string deviceGroupId = "", string deviceGroupName = "", string groupLevel = "")
        {
            string path = "/aep_device_group_management/deviceGroups";
            Dictionary<string, string> headers = null;
            Dictionary<string, string> param = new Dictionary<string, string>();
            param.Add("pageNow", pageNow);
            param.Add("pageSize", pageSize);
            param.Add("productId", productId);
            param.Add("deviceGroupId", deviceGroupId);
            param.Add("deviceGroupName", deviceGroupName);
            param.Add("groupLevel", groupLevel);

            string version = "20230218035819";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, null, version, application, key, "GET");
            if (response != null)
                return response;
            return null;
        }
        //参数MasterKey: 类型String, 参数可以为空
        //  描述:
        //参数productId: 类型long, 参数可以为空
        //  描述:产品ID，查询单产品分组下已关联的设备列表或产品下未关联的设备列表时必填
        //参数searchValue: 类型String, 参数可以为空
        //  描述:可查询：设备ID，设备名称，设备编号或者IMEI号；仅支持单产品分组查询
        //参数pageNow: 类型long, 参数不可以为空
        //  描述:当前页数
        //参数pageSize: 类型long, 参数不可以为空
        //  描述:每页条数
        //参数deviceGroupId: 类型long, 参数可以为空
        //  描述:群组ID：1.有值则查询该群组已关联的设备信息列表。2.为空则查询该产品下未关联的设备信息列表
        public static string QueryGroupDeviceList(string appKey, string appSecret, string pageNow, string pageSize, string MasterKey = "", string productId = "", string searchValue = "", string deviceGroupId = "")
        {
            string path = "/aep_device_group_management/groupDeviceList";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = new Dictionary<string, string>();
            param.Add("productId", productId);
            param.Add("searchValue", searchValue);
            param.Add("pageNow", pageNow);
            param.Add("pageSize", pageSize);
            param.Add("deviceGroupId", deviceGroupId);

            string version = "20190615001540";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, null, version, application, key, "GET");
            if (response != null)
                return response;
            return null;
        }
        //参数MasterKey: 类型String, 参数可以为空
        //  描述:
        //参数body: 类型json, 参数不可以为空
        //  描述:body,具体参考平台api说明
        public static string UpdateDeviceGroupRelation(string appKey, string appSecret, string body, string MasterKey = "")
        {
            string path = "/aep_device_group_management/deviceGroupRelation";
            Dictionary<string, string> headers = new Dictionary<string, string>();
            headers.Add("MasterKey", MasterKey);

            Dictionary<string, string> param = null;
            string version = "20190615001526";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, body, version, application, key, "PUT");
            if (response != null)
                return response;
            return null;
        }
        //参数productId: 类型long, 参数不可以为空
        //  描述:
        //参数deviceId: 类型String, 参数不可以为空
        //  描述:
        public static string getGroupDetailByDeviceId(string appKey, string appSecret, string productId, string deviceId)
        {
            string path = "/aep_device_group_management/groupOfDeviceId";
            Dictionary<string, string> headers = null;
            Dictionary<string, string> param = new Dictionary<string, string>();
            param.Add("productId", productId);
            param.Add("deviceId", deviceId);

            string version = "20211014095939";

            string application = appKey;
            string key = appSecret;


            string response = AepHttpRequest.SendAepHttpRequest(path, headers, param, null, version, application, key, "GET");
            if (response != null)
                return response;
            return null;
        }

    }
}
