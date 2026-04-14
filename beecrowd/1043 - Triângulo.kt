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

fun isTriangle(a: Double, b: Double, c: Double): Boolean {
    val sides = arrayOf(a, b, c)

    sides.sort()

    return sides[2] < sides[0] + sides[1]
}

fun perimeter(a: Double, b: Double, c: Double): Double {
    return a + b + c
}

fun trapezeArea(a: Double, b: Double, c: Double): Double {
    return (a + b) * c / 2
}

fun main(args: Array<String>) {

    val console = Console()

    val a = console.readDouble()
    val b = console.readDouble()
    val c = console.readDouble()

    if (isTriangle(a, b, c)) {
        println("Perimetro = %.1f".format(Locale.US, perimeter(a, b, c)))
    } else {
        println("Area = %.1f".format(Locale.US, trapezeArea(a, b, c)))
    }
}