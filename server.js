const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const path = require('path');
const cors = require('cors');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

// Enable CORS for all routes
app.use(cors());

// Serve static files from the current directory
app.use(express.static(__dirname));

// Serve the main HTML file
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'nodered.html'));
});

// WebSocket connection handling
wss.on('connection', (ws) => {
  console.log('New WebSocket connection established');

  // Forward messages from Node-RED to connected clients
  const nodeRedWs = new WebSocket('ws://192.168.204.116:1880/ws/co2');
  
  nodeRedWs.on('message', (data) => {
    if (ws.readyState === WebSocket.OPEN) {
      ws.send(data);
    }
  });

  nodeRedWs.on('error', (error) => {
    console.error('Node-RED WebSocket error:', error);
  });

  nodeRedWs.on('close', () => {
    console.log('Node-RED WebSocket connection closed');
  });

  ws.on('close', () => {
    console.log('Client WebSocket connection closed');
    nodeRedWs.close();
  });
});

// Proxy the CSV download endpoint
app.get('/download-co2', async (req, res) => {
  try {
    const response = await fetch('http://192.168.204.116:1880/download-co2');
    const data = await response.blob();
    
    res.setHeader('Content-Type', 'text/csv');
    res.setHeader('Content-Disposition', `attachment; filename=co2_log_${new Date().toISOString().slice(0,10)}.csv`);
    res.send(data);
  } catch (error) {
    console.error('Error proxying CSV download:', error);
    res.status(500).send('Error generating CSV file');
  }
});

const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
}); 