import java.util.*

class Console {
    private val buffer = ArrayDeque<String>()

    private fun fillBuffer() {
        if(buffer.isEmpty()) {
            val str = readLine()!!
            val pieces = str.split(" ")

            for (piece in pieces) {
                buffer.add(piece)
            }
        }
    }

    fun readInt(): Int {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toInt()
    }

    fun readDouble(): Double {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toDouble()
    }

    fun readString(): String {
        fillBuffer()

        val result = buffer.removeFirst()

        return result
    }

    fun readLong(): Long {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toLong()
    }

    fun readFloat(): Float {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toFloat()
    }
}

fun main(args: Array<String>) {

    val console = Console()

    val values = ArrayList<Int>()

    for (i in 0..2) {
        val value = console.readInt()
        values.add(value)
    }

    val orderedValues = values.toMutableList()

    orderedValues.sort()

    for (value in orderedValues) {
        println(value)
    }

    println("")

    for (value in values) {
        println(value)
    }
}