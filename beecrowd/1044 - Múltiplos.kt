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

    val areMultiples = {a: Int, b: Int ->
        a % b == 0 || b % a == 0
    };

    val a = console.readInt()
    val b = console.readInt()

    if(areMultiples(a, b)) {
        println("Sao Multiplos")
    } else {
        println("Nao sao Multiplos")
    }
}
