using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Target
{
    private static GameObject targetObject;

    public static void Set(GameObject newObject)
    {
        if (newObject.CompareTag("StationaryFlag"))
        {
            // stationary flags are always on top of a capture point
            newObject = newObject.transform.parent.gameObject;
        }
        if (newObject.CompareTag("CapturePoint"))
        {
            // do not set it as a target unless we have a connection
            if (newObject.GetComponent<CapturePointController>().Connect())
            {
                targetObject = newObject;
            }
        }
        else if (newObject.CompareTag("Flag"))
        {
            targetObject = newObject;
        }
    }

    private static GameObject Get()
    {
        if (targetObject == null) return null;
        // too far away, not a target anymore
        if (targetObject.transform.position.magnitude > 2.0f)
        {
            targetObject = null;
        }
        else if (targetObject.CompareTag("CapturePoint"))
        {
            // TODO maybe handle this server side?
            var cp = targetObject.GetComponent<CapturePointController>();
            var target = cp.CapturePoint.Team;
            var team = GameController.Team;
            var carrying = GameController.CarryingFlag;
            if ((target == team && !carrying) || (target != team && carrying))
            {
                targetObject = null;
            }
        }
        return targetObject;
    }

    public static string GetTypeName()
    {
        var target = Get();
        if (target == null) return "";
        if (target.CompareTag("CapturePoint")) return "cp";
        if (target.CompareTag("Flag"))
        {
            // TODO this needs to be fixed on the server side
            if (GameController.Player == "p1") return "p2";
            if (GameController.Player == "p2") return "p1";
        }
        return "";
    } 
}
