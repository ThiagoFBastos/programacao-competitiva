import java.util.*

class Time(private var seconds: Int) {
    private var hour: Int = 0
    private var minute: Int = 0
    private var second: Int = 0

    init {
        val hourSeconds = 60 * 60
        val minuteSeconds = 60

        hour = seconds / hourSeconds
        seconds %= hourSeconds
        minute = seconds / minuteSeconds
        seconds %= minuteSeconds
        second = seconds
    }

    fun formatTime():String {
        return "${hour}:${minute}:${second}"
    }
}

fun main(args: Array<String>) {

    val seconds = readLine()!!.toInt()

    val time = Time(seconds)

    println(time.formatTime())
}