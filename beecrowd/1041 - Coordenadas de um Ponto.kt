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

fun roundToOneDecimalPlace(number: Double): Double = (number * 10).toInt() / 10.0

fun main(args: Array<String>) {

    val console = Console()

    val x = console.readDouble()
    val y = console.readDouble()

    if (x == 0.0 && y == 0.0) {
        println("Origem")
    } else if (x == 0.0) {
        println("Eixo Y")
    } else if (y == 0.0) {
        println("Eixo X")
    } else if (x > 0.0 && y > 0.0) {
        println("Q1")
    } else if(x > 0.0 && y < 0.0) {
        println("Q4")
    } else if (x < 0.0 && y > 0.0) {
        println("Q2")
    } else {
        println("Q3")
    }
}