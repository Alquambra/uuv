const express = require('express');
const path = require('path');
const yaml = require('js-yaml');
const fs = require('fs');




const PORT = 8080;
const app = express();

app.use(express.static('static'));


app.get('/', (req, res) => {
    res.sendFile(path.resolve(__dirname, 'templates', 'main.html'));
});

app.get('/params', (req, res) => {
    try {
        let oceanicContents = fs.readFileSync('/home/ubuntu/drone_ros/src/drone/config/oceanic.yaml', 'utf8');
        let oceanic_params = yaml.load(oceanicContents);
        let pidContents = fs.readFileSync('/home/ubuntu/drone_ros/src/drone/config/pid.yaml', 'utf8');
        let pid_params = yaml.load(pidContents)
        data = {'oceanic': oceanic_params, 'pid': pid_params};
        res.send(data);
    } catch(e) {
        console.log(e);
        res.send({"status": "error"})
    }
});


app.post('/save_params', (req, res) => {
    
});





app.listen(PORT, () => {
    console.log(`Server started at ${PORT}`);
});