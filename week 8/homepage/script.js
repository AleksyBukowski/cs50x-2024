let counter = 1
function photoChange() {
    let pid = counter % 5;
    document.querySelector("#cats").setAttribute("src", pid+".jpg")
    counter += 1;

}

setInterval(photoChange, 4000);
