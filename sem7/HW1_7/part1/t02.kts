interface Media {
    val title: String
    abstract fun play()
}

class Audio(override val title: String, val composer: String) : Media {
    override fun play() {
        println("Playing audio: $title by $composer")
    }
}

val audio = Audio("Symphony No. 5", "Beethoven")
audio.play()

