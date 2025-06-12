class Timer {
    // default values
    constructor(hr, min, sec) {
        this.hours = 0;
        this.minutes = 0;
        this.seconds = 0;
        this.total = 0;
    }

    startTime() {
        this.initialize();
        this.hide();



        let temp = this.total;
        let hr = this.hours
        let min = this.minutes;
        let sec = this.seconds;

        // initialize timer display
        if (hr < 10) {
            hr = "0" + hr;
        }
        if (min < 10) {
            min = "0" + min;
        }
        if (sec < 10) {
            sec = "0" + sec;
        }
        document.getElementById("hr-display").innerHTML = hr;
        document.getElementById("min-display").innerHTML = min;
        document.getElementById("sec-display").innerHTML = sec;

        // switch input interface to display
        document.getElementById("selection-title").innerHTML = "time left:";
        document.getElementById("timer-start").style.display = "none";

        // timer logic
        let interval = setInterval(function () {
            temp = temp - 1;

            hr = Math.floor(temp / 3600);
            min = Math.floor((temp % 3600) / 60);
            sec = Math.floor(((temp % 3600) % 60));

            // if (hr < 10) {
            //     hr = "0" + hr;
            // }

            // if (min < 10) {
            //     min = "0" + min;
            // }

            // if (sec < 10) {
            //     sec = "0" + sec;
            // }
            document.getElementById("hr-display").innerHTML = hr;
            document.getElementById("min-display").innerHTML = min;
            document.getElementById("sec-display").innerHTML = sec;

            // when timer runs out, clear the timer and revert to original status
            if (temp <= 0) {
                document.getElementById("selection-title").innerHTML = "click to select amount of time:";
                document.getElementById("timer-start").style.display = "block";
                document.getElementById("timer-interface").style.display = "block";
                document.getElementById("timer-display").style.display = "none";
                clearInterval(interval);
            }
        }, 1000);

    }

    unhide() {
        document.getElementById("timer-interface").style.display = "block";
        document.getElementById("timer-display").style.display = "none";
    }
    hide() {
        document.getElementById("timer-interface").style.display = "none";
        document.getElementById("timer-display").style.display = "block";

    }

    initialize() {
        this.hours = document.getElementById("hr").valueAsNumber;
        this.minutes = document.getElementById("min").valueAsNumber;
        this.seconds = document.getElementById("sec").valueAsNumber;

        if (!this.hours) {
            this.hours = 0;
        }
        if (!this.minutes) {
            this.minutes = 0;
        }
        if (!this.seconds) {
            this.seconds = 0;
        }
        this.total = (this.hours * 3600 + this.minutes * 60 + this.seconds);
    }
}

// create object instance; updates via user input/page interaction
let timer = new Timer;