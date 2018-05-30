using AJObject = UnityEngine.AndroidJavaObject;

public static class Bluetooth
{
    private const string SPP_UUID = "00001101-0000-1000-8000-00805F9B34FB";

    public static bool Connect(string address)
    {
        try
        {
            var adapter = new AJObject("android.bluetooth.BluetoothAdapter")
                .CallStatic<AJObject>("getDefaultAdapter");
            // force enable bluetooth
            adapter.Call<bool>("enable");

            var device = adapter.Call<AJObject>("getRemoteDevice", address);
            var uuid = new AJObject("java.util.UUID")
                    .CallStatic<AJObject>("fromString", SPP_UUID);

            var socket = device.Call<AJObject>(
                            "createInsecureRfcommSocketToServiceRecord", uuid);

            socket.Call("connect");
            // at this point, connection is made, no further action necessary
            socket.Call("close");
            return true;
        }
        catch
        {
            return false;
        }
    }
}
