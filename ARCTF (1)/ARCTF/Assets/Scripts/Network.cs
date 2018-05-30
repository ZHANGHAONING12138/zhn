using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public static class Network
{
    //private const string SERVER_ADDR = "http://35.196.67.153";
    private const string SERVER_ADDR = "http://127.0.0.1:5000";

    public static void LoadPermanentState(GameState state,
                    OnStateRead onStateRead)
    {
        var operation = new UnityWebRequest
        {
            url = SERVER_ADDR + "/hello",
            method = UnityWebRequest.kHttpVerbGET,
            downloadHandler = new DownloadHandlerBuffer()
        }.SendWebRequest();
        operation.completed += delegate(AsyncOperation asyncOperation)
        { 
            OnLoadCompleted(asyncOperation, state);
            onStateRead();
        };
    }

    public static void LoadTransientState(string player,
                    TransientState transientState)
    {
        // TODO we need to make the server use POST instead of GET
        /*var json = JsonUtility.ToJson(playerState);
        var data = System.Text.Encoding.UTF8.GetBytes(json);*/
        var operation = new UnityWebRequest
        {
            url = GetReportURL(player),
            method = UnityWebRequest.kHttpVerbGET, // TODO
            //uploadHandler = new UploadHandlerRaw(data),
            downloadHandler = new DownloadHandlerBuffer()
        }.SendWebRequest();
        operation.completed += delegate(AsyncOperation asyncOperation)
        {
            OnLoadCompleted(asyncOperation, transientState);
        };
    }

    private static void OnLoadCompleted(AsyncOperation operation, object obj)
    {
        var request = ((UnityWebRequestAsyncOperation) operation).webRequest;
        if (request.isNetworkError || request.isHttpError) return;
        var json = request.downloadHandler.text;
        JsonUtility.FromJsonOverwrite(request.downloadHandler.text, obj);
    }

    public delegate void OnStateRead();

    // this function will be removed when the server starts accepting POST
    private static string GetReportURL(string player)
    {
        return SERVER_ADDR + "/report_location"
            + "?player=" + player
            + "&latitude=" + Location.Latitude
            + "&longitude=" + Location.Longitude
            + "&connected=" + Target.GetTypeName();
    }
}
