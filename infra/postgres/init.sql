-- Schema oficial da Mini Estação de Telemetria 4.0

-- Cadastro dos dispositivos da planta
CREATE TABLE IF NOT EXISTS devices (
    id SERIAL PRIMARY KEY,
    device_uid VARCHAR(64) UNIQUE NOT NULL,
    nome VARCHAR(64) NOT NULL,
    tipo VARCHAR(32) NOT NULL,
    criado_em TIMESTAMPTZ DEFAULT NOW()
);

-- Leituras de telemetria enviadas pelos dispositivos
CREATE TABLE IF NOT EXISTS telemetry (
    id SERIAL PRIMARY KEY,
    device_id INT NOT NULL REFERENCES devices(id),
    tipo VARCHAR(32) NOT NULL,          -- temperatura, vibração, luminosidade...
    valor NUMERIC NOT NULL,
    unidade VARCHAR(16),
    timestamp TIMESTAMPTZ DEFAULT NOW()
);
